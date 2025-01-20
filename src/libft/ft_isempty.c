#include "../../include/minishell.h"

int	ft_isempty(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!ft_isspace(command[i]))
			return (0);
		i++;
	}
	return (1);
}
