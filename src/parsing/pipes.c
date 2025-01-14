#include "../../include/minishell.h"

int	count_segments(char *command, char sep)
{
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;

	count = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (!command)
		return (0);
	i = 0;
	while (command[i])
	{
		if (!update_quote_state(command[i], &in_single_quote, &in_double_quote)
			&& command[i] == sep && !in_single_quote && !in_double_quote)
			count++;
		i++;
	}
	return (count + 1);
}

void	split_command(char **result, char *command, char sep)
{
	int		start;
	int		index;
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;

	start = 0;
	index = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (!result || !command)
		return ;
	i = 0;
	while (command[i])
	{
		if (!update_quote_state(command[i], &in_single_quote, &in_double_quote)
			&& command[i] == sep && !in_single_quote && !in_double_quote)
		{
			command[i] = '\0';
			result[index++] = ft_strdup(&command[start]);
			start = i + 1;
		}
		i++;
	}
	result[index++] = ft_strdup(&command[start]);
	result[index] = NULL;
}

char	**split_pipes(char *command)
{
	char	**result;
	int		segments;

	if (!command)
		return (NULL);
	segments = count_segments(command, '|');
	result = malloc(sizeof(char *) * (segments + 1));
	if (!result)
		return (NULL);
	split_command(result, command, '|');
	return (result);
}
