#include "../../include/minishell.h"

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	bool	single_quote;
	bool	double_quote;

	i = 0;
	j = 0;
	single_quote = false;
	double_quote = false;
	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (!update_quote_state(str[i], &single_quote, &double_quote))
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	if (single_quote || double_quote)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

bool	update_quote_state(char c, bool *in_single_quote, bool *in_double_quote)
{
	if (c == '\'' && !*in_double_quote)
	{
		*in_single_quote = !*in_single_quote;
		return (true);
	}
	if (c == '\"' && !*in_single_quote)
	{
		*in_double_quote = !*in_double_quote;
		return (true);
	}
	return (false);
}
