#include "../../include/minishell.h"

static bool	check_dir(char **path, char *command, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		print_error(command);
		print_error(" : Is a directory\n");
		data->exit_code = 126;
		return (false);
	}
	return (true);
}

static bool	cmd_exist(char **path, t_data *data, char *command)
{
	if (!ft_strchr(command, '/'))
		*path = find_cmd(data, command, data->env);
	else
		absolute_path(path, command, data);
	if (!(*path) && data->exit_code == -1)
		free_all(data, NULL, data->exit_code);
	if (!(*path))
	{
		data->exit_code = 127;
		return (false);
	}
	if (access((*path), X_OK))
	{
		perror(*path);
		free((*path));
		(*path) = NULL;
		data->exit_code = 126;
		return (false);
	}
	if (!check_dir(path, command, data))
		return (false);
	return (true);
}

static void	redirect_in_out(t_data *data, t_command *commands, int *pip)
{
	close(pip[0]);
	if (commands->infile >= 0)
	{
		dup2(commands->infile, 0);
		close(commands->infile);
	}
	if (commands->outfile >= 0)
	{
		dup2(commands->outfile, 1);
		close(commands->outfile);
	}
	else if (commands->next != data->commands)
		dup2(pip[1], 1);
	close(pip[1]);
}

static void	built(int *pip, t_command *commands, t_data *data)
{
	close(pip[0]);
	if (commands->outfile < 0 && commands->next != data->commands)
		commands->outfile = pip[1];
	else
		close(pip[1]);
	launch_builtin(data, commands);
}

void	child_process(t_data *data, t_command *commands, int *pip)
{
	char	*path;
	char	**env;

	path = NULL;
	if (commands->skip_cmd)
		data->exit_code = 1;
	else if (is_builtin(commands->command_param[0]))
		built(pip, commands, data);
	else if (cmd_exist(&path, data, commands->command_param[0]))
	{
		redirect_in_out(data, commands, pip);
		env = lst_to_arr(data->env);
		if (!env)
			free_all(data, ERR_MALLOC, EXT_MALLOC);
		rl_clear_history();
		reset_sigquit();
		execve(path, commands->command_param, env);
		free(env);
	}
	if (path)
		free(path);
	free_all(data, NULL, data->exit_code);
}
