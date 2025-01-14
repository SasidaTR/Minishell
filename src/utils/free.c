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

void	free_all(t_command *commands, int exit_program)
{
	if (commands->command)
		free(commands->command);
	if (exit_program == 1)
		exit(exit_program);
}
