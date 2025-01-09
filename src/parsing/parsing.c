#include "../../include/minishell.h"

bool	parsing(t_command *commands, char **env, t_data *data)
{
	char	**pipe_commands;
	char	*no_quote_commands;
	char	**final_command;
	int		i;

	pipe_commands = advanced_split(commands->command, '|');
	if (!pipe_commands || !pipe_commands[0])
	{
		free_array(pipe_commands);
		return (false);
	}
	i = 0;
	while (pipe_commands[i])
	{
		no_quote_commands = remove_quotes(pipe_commands[i]);
		if (!no_quote_commands)
		{
			printf("Error: Unclosed quotes in command: %s\n", pipe_commands[i]);
			free_array(pipe_commands);
			return (false);
		}
		final_command = ft_split(no_quote_commands, ' ');
		if (!final_command)
		{
			printf("Error: Failed to split command: %s\n", no_quote_commands);
			free(no_quote_commands);
			free_array(pipe_commands);
			return (false);
		}
		execute_command(final_command, env, data);
		free_array(final_command);
		free(no_quote_commands);
		i++;
	}
	free_array(pipe_commands);
	return (true);
}
