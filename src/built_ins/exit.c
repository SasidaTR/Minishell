#include "../../include/minishell.h"

int	ft_exit(t_command *commands, t_data *data)
{
	(void)data;
	free(commands->command);
	exit(1);
	return (0);
}
