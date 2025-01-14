#include "../../include/minishell.h"


int ft_echo(t_command *commands)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (commands->split_command[i] && ft_strncmp(commands->split_command[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (commands->split_command[i])
	{
		printf("%s", commands->split_command[i]);
		if (commands->split_command[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
