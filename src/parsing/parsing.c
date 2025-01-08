#include "../../include/minishell.h"

bool	parsing(char *command, char **env)
{
	char	**pipe_commands;
	char	*parsed_command;
	char	**split_args;

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
			printf("Error: Unclosed quotes in command: %s\n", pipe_commands[i]);
			free_array(pipe_commands);
			return (false);
		}
		split_args = ft_split(parsed_command, ' ');
		if (!split_args)
		{
			printf("Error: Failed to split command: %s\n", parsed_command);
			free(parsed_command);
			free_array(pipe_commands);
			return (false);
		}
		execute_command(split_args, env);
		free_array(split_args);
		free(parsed_command);
	}
	free_array(pipe_commands);
	return (true);
}
