#include "../../include/minishell.h"

char	*quotes(char *command)
{
	char	*result;
	int		i;
	int		j;
	int		single_quote;
	int		double_quote;

	single_quote = 0;
	double_quote = 0;
	if (!command)
		return (NULL);
	result = malloc(ft_strlen(command) + 1);
	if (!result)
		return (NULL);
	for (i = 0, j = 0; command[i]; i++)
	{
		if (command[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (command[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else
			result[j++] = command[i];
	}
	result[j] = '\0';
	return (single_quote || double_quote) ? (free(result), NULL) : result;
}

static int	is_separator(char c, char sep, bool in_single_quote, bool in_double_quote)
{
	return (c == sep && !in_single_quote && !in_double_quote);
}

char	**advanced_split(char *command, char sep)
{
	char	**result;
	int		i;
	int		start;
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	start = 0;
	count = 0;
	in_single_quote = false;
	in_double_quote = false;
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
	count++;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	for (i = 0, count = 0, start = 0; command[i]; i++)
	{
		if (is_separator(command[i], sep, in_single_quote, in_double_quote))
		{
			command[i] = '\0';
			result[count++] = ft_strdup(&command[start]);
			start = i + 1;
		}
	}
	result[count++] = ft_strdup(&command[start]);
	result[count] = NULL;
	return (result);
}
