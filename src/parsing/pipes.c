#include "../../include/minishell.h"

static int	is_separator(char c, char sep, bool in_single_quote, bool in_double_quote)
{
	if (c == sep && !in_single_quote && !in_double_quote)
		return (1);
	return (0);
}

static int	count_segments(char *command, char sep)
{
	int		count;
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	count = 0;
	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	while (command[i])
	{
		if (command[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (command[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (is_separator(command[i], sep, in_single_quote, in_double_quote))
			count++;
		i++;
	}
	return (count + 1);
}

static void	split_command(char **result, char *command, char sep)
{
	int		i;
	int		start;
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	start = 0;
	count = 0;
	while (command[i])
	{
		if (command[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (command[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (is_separator(command[i], sep, in_single_quote, in_double_quote))
		{
			command[i] = '\0';
			result[count] = ft_strdup(&command[start]);
			count++;
			start = i + 1;
		}
		i++;
	}
	result[count] = ft_strdup(&command[start]);
	result[count + 1] = NULL;
}

char	**advanced_split(char *command, char sep)
{
	char	**result;
	int		segment_count;

	if (!command)
		return (NULL);
	segment_count = count_segments(command, sep);
	result = malloc(sizeof(char *) * (segment_count + 1));
	if (!result)
		return (NULL);
	split_command(result, command, sep);
	return (result);
}
