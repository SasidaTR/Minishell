#include "../../include/minishell.h"

void	free_all(char *command, int exit_program)
{
	if (command)
		free(command);
	if (exit_program == 1)
		exit(exit_program);
}