#include "../../include/minishell.h"

bool	is_empty(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!is_space(command[i]))
			return (false);
		i++;
	}
	return (true);
}
