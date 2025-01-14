#include "../../include/minishell.h"


int ft_echo(t_command *command)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (command->split_command[i] && ft_strncmp(command->split_command[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (command->split_command[i])
	{
		printf("%s", command->split_command[i]);
		if (command->split_command[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
