#include "../../include/minishell.h"

int ft_exit(t_command *commands, t_data *data)
{
	data->exit_code = 0;
	printf("exit\n");
	if (commands->split_command[1])
	{
		if (!ft_isnumber(commands->split_command[1]))
		{
			printf("exit %s: numeric arguments required\n", commands->split_command[1]);
			data->exit_code = 2;
		}
		else if (commands->split_command[2])
		{
			printf("exit: too many arguments");
			return (1);
		}
		else
		{
			data->exit_code = ft_atoi(commands->split_command[1]);
			if (data->exit_code < 0 || data->exit_code > 255)
				data->exit_code %= 256;
		}
	}
	free(commands->command);
	free_array(data->env);
	exit(data->exit_code);
	return (0);
}
