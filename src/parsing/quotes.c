#include "../../include/minishell.h"

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	bool	single_quote;
	bool	double_quote;

	if (!str)
		return (NULL);
	single_quote = false;
	double_quote = false;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else
		{
			result[j] = str[i];
			j++;
		}
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
