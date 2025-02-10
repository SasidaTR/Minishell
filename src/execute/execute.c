#include "../../include/minishell.h"

static void	parent_process(t_data *data, t_command *commands, int *pip)
{
	close(pip[1]);
	if (commands->infile >= 0)
		close(commands->infile);
	if (commands->infile == -2)
		commands->infile = pip[0];
	if (commands->next != data->commands && commands->next->infile == -2)
		commands->next->infile = pip[0];
	else
		close(pip[0]);
}

static bool	execute_cmd(t_data *data, t_command *commands, int *pip)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all(data, ERR_FORK, EXT_FORK);
	else if (!g_signal_pid)
	{
		if (commands->command_param && commands->command_param[0])
			child_process(data, commands, pip);
		else
			free_all(data, NULL, 0);
	}
	else
		parent_process(data, commands, pip);
	return (true);
}

static void	wait_all(t_data *data)
{
	int		status;
	int		pid;
	int		len;
	t_command	*tmp;

	tmp = data->commands;
	len = len_cmd(tmp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		if (tmp->outfile >= 0)
			close(tmp->outfile);
		if (tmp->infile >= 0)
			close(tmp->infile);
		tmp = tmp->next;
	}
}

bool	is_builtin(char *command)
{
	if (!command)
		return (false);
	if (!ft_strncmp("echo", command, INT_MAX) || !ft_strncmp("cd", command, INT_MAX) \
	|| !ft_strncmp("pwd", command, INT_MAX) || !ft_strncmp("export", command, INT_MAX) \
	|| !ft_strncmp("unset", command, INT_MAX) || !ft_strncmp("env", command, INT_MAX) \
	|| !ft_strncmp("exit", command, INT_MAX))
		return (true);
	return (false);
}

bool	execute(t_data *data)
{
	t_command	*tmp;
	int		*pip;

	pip = data->pip;
	tmp = data->commands;
	if (tmp && tmp->skip_cmd == false && tmp->next == tmp && tmp->command_param[0] \
		&& is_builtin(tmp->command_param[0]))
		return (launch_builtin(data, tmp));
	if (pipe(pip) == -1)
		return (false);
	execute_cmd(data, tmp, pip);
	tmp = tmp->next;
	while (tmp != data->commands)
	{
		if (pipe(pip) == -1)
			return (-1);
		execute_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(data);
	return (true);
}
