#include "../../include/minishell.h"

bool	parsing(char *command, char **env)
{
	char	**pipe_commands;
	char	*parsed_command;

	pipe_commands = advanced_split(command, '|');
	if (!pipe_commands || !pipe_commands[0])
	{
		free_array(pipe_commands);
		return (false);
	}
	for (int i = 0; pipe_commands[i]; i++)
	{
		parsed_command = remove_quotes(pipe_commands[i]);
		if (!parsed_command)
		{
			printf("Error: Unclosed quotes in command\n");
			free_array(pipe_commands);
			return (false);
		}
		execute_command(ft_split(parsed_command, ' '), env);
		free(parsed_command);
	}
	free_array(pipe_commands);
	return (true);
}
