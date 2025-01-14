#include "../../include/minishell.h"

int	ft_cd(t_command *commands, t_data *data)
{
	if (!commands || !commands->split_command || count_args(commands->split_command) != 2)
	{
		printf("Usage: cd <directory>\n");
		if (data)
			data->exit_code = 1;
		return (1);
	}

	if (chdir(commands->split_command[1]) != 0)
	{
		perror("cd");
		if (data)
			data->exit_code = 1;
		return (1);
	}

	// char cwd[PATH_MAX];
	// if (getcwd(cwd, sizeof(cwd)))
	// {
	// 	update_env(data, "PWD", cwd);
	// }
	// else
	// {
	// 	perror("getcwd");
	// }

	if (data)
		data->exit_code = 0;
	return (0);
}