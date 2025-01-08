#include "../../include/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_all(char *command, int exit_program)
{
	if (command)
		free(command);
	if (exit_program == 1)
		exit(exit_program);
}
