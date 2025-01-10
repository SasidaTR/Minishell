#include "../../include/minishell.h"

bool	parsing(t_command *commands, char **env, t_data *data)
{
	char	*no_quote_command;
	int		i;

	commands->commands = advanced_split(commands->command, '|');
	if (!commands->commands || !commands->commands[0])
	{
		free_array(commands->commands);
		return (false);
	}
	i = 0;
	while (commands->commands[i])
	{
		no_quote_command = remove_quotes(commands->commands[i]);
		if (!no_quote_command)
		{
			printf("Error: Unclosed quotes in command: %s\n", commands->commands[i]);
			free_array(commands->commands);
			return (false);
		}
		commands->split_command = ft_split(no_quote_command, ' ');
		if (!commands->split_command[i])
		{
			printf("Error: Failed to split command: %s\n", no_quote_command);
			free(no_quote_command);
			free_array(commands->commands);
			return (false);
		}
		if (!handle_redirections(commands))
		{
			free_array(commands->split_command);
			free(no_quote_command);
			free_array(commands->commands);
			return (false);
		}
		execute_command(commands, env, data);
		free_array(commands->split_command);
		free(no_quote_command);
		i++;
	}
	free_array(commands->commands);
	return (true);
}
