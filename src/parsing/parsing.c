#include "../../include/minishell.h"

static char	*remove_quotes(char *str)
{
	char	*result;
	int		i, j;
	bool	single_quote = false, double_quote = false;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	for (i = 0, j = 0; str[i]; i++)
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else
			result[j++] = str[i];
	}
	result[j] = '\0';
	return (single_quote || double_quote) ? (free(result), NULL) : result;
}

static char	**split_pipes(char *command)
{
	return advanced_split(command, '|');
}

bool	parsing(char *command, char **env)
{
	char	**pipe_commands;
	char	*parsed_command;

	pipe_commands = split_pipes(command);
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
