#include "../../include/minishell.h"

int	ft_env(t_command *commands, t_data *data)
{
	int	i;

	i = 0;
	if (commands->split_command[2])
	{
		printf("exit: too many arguments");
		return (1);
	}
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
