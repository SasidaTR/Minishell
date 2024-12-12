#include "../../include/minishell.h"

char	*quotes(char *command)
{
	char	*result;
	int		i;
	int		j;
	int		single_quote;
	int		double_quote;

	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	if (!command)
		return (NULL);
	result = malloc(ft_strlen(command) + 1);
	if (!result)
		return (NULL);
	while (command[i])
	{
		if (command[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (command[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else
			result[j++] = command[i];
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