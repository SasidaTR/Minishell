#include "../../include/minishell.h"


int	ft_exit(t_command *command, t_data *data)
{
	(void)data;
    free_all(command, 1);
	return(0);
}

