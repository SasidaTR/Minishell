#include "../../include/minishell.h"

char	**pipes(char *command)
{
	char	**commands;

	if (!command || !*command)
		return (NULL);
	commands = ft_split(command, '|');
	return (commands);
}