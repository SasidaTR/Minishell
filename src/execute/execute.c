/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:41:53 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:41:53 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool	execute_command(t_data *data, t_command *commands, int *pip)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		free_all(data, ERR_FORK, EXT_FORK);
	else if (pid == 0)
	{
		if (commands->command_param && commands->command_param[0])
			child_process(data, commands, pip);
		else
			free_all(data, NULL, 0);
	}
	else
	{
		g_signal = pid;
		parent_process(data, commands, pip);
	}
	return (true);
}

static void	wait_all(t_data *data)
{
	int			status;
	pid_t		pid;
	int			len;
	t_command	*temp;

	temp = data->commands;
	len = len_command(temp);
	while (len--)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == g_signal)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
	}
	g_signal = 0;
}

bool	is_builtin(char *command)
{
	if (!command)
		return (false);
	if (!ft_strncmp("echo", command, INT_MAX)
		|| !ft_strncmp("cd", command, INT_MAX)
		|| !ft_strncmp("pwd", command, INT_MAX)
		|| !ft_strncmp("export", command, INT_MAX)
		|| !ft_strncmp("unset", command, INT_MAX)
		|| !ft_strncmp("env", command, INT_MAX)
		|| !ft_strncmp("exit", command, INT_MAX))
		return (true);
	return (false);
}

bool	execute(t_data *data)
{
	t_command	*temp;
	int			*pip;

	pip = data->pip;
	temp = data->commands;
	if (temp && temp->skip_cmd == false
		&& temp->next == temp && temp->command_param[0]
		&& is_builtin(temp->command_param[0]))
		return (run_builtin(data, temp));
	if (pipe(pip) == -1)
	{
		data->exit_code = 1;
		return (false);
	}
	execute_command(data, temp, pip);
	temp = temp->next;
	while (temp != data->commands)
	{
		if (pipe(pip) == -1)
			return (-1);
		execute_command(data, temp, pip);
		temp = temp->next;
	}
	wait_all(data);
	return (true);
}
