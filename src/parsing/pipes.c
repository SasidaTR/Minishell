#include "../../include/minishell.h"

int count_segments(char *command, char sep)
{
	int count = 0;
	bool in_single_quote = false, in_double_quote = false;

	if (!command)
		return 0;
	for (int i = 0; command[i]; i++)
	{
		if (!update_quote_state(command[i], &in_single_quote, &in_double_quote) &&
		    command[i] == sep && !in_single_quote && !in_double_quote)
			count++;
	}
	return count + 1;
}

void split_command(char **result, char *command, char sep)
{
	int start = 0, index = 0;
	bool in_single_quote = false, in_double_quote = false;

	if (!result || !command)
		return;
	for (int i = 0; command[i]; i++)
	{
		if (!update_quote_state(command[i], &in_single_quote, &in_double_quote) &&
		    command[i] == sep && !in_single_quote && !in_double_quote)
		{
			command[i] = '\0';
			result[index++] = ft_strdup(&command[start]);
			start = i + 1;
		}
	}
	result[index++] = ft_strdup(&command[start]);
	result[index] = NULL;
}

char **split_pipes(char *command)
{
	char **result;
	int segments;

	if (!command)
		return NULL;
	segments = count_segments(command, '|');
	result = malloc(sizeof(char *) * (segments + 1));
	if (!result)
		return NULL;
	split_command(result, command, '|');
	return result;
}
