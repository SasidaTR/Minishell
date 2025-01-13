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
	if (commands->split_command)
		free_array(commands->split_command);
	if (commands->commands)
		free_array(commands->commands);
	if (exit_program == 1)
		exit(exit_program);
}
