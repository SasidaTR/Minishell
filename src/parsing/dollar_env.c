#include "../../include/minishell.h"

static int	ft_search(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

static int	end_word(char *str, char *env)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		++i;
	if (i == ft_search(env, '='))
		return (i);
	return (0);
}

int	exist_in_env(char *line, int *i, t_data *data)
{
	t_list	*temp;
	int		len;

	if (line[*i + 1] == '?' || line[*i + 1] == '$')
		return (2);
	temp = data->env;
	len = len_list(temp);
	while (len--)
	{
		if (ft_strncmp(temp->str, &line[*i + 1], \
			end_word(&line[*i + 1], temp->str)) == 0)
		{
			*i += ft_strlen(temp->str) - \
				ft_strlen(ft_strchr(temp->str, '=')) + 1;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*get_elem_env(t_list *env, char *key)
{
	t_list	*temp;
	int		len;
	int		t;

	if (!key)
		return (NULL);
	temp = env;
	len = len_list(temp);
	t = ft_strlen(key);
	while (len--)
	{
		if (ft_strncmp(temp->str, key, t) == 0)
		{
			len = 0;
			while (temp->str[len])
				if (temp->str[len++] == '=')
					break ;
			return (ft_strdup(&(temp->str[len])));
		}
		temp = temp->next;
	}
	return (NULL);
}

char	*get_dollar_word(char *line, int size)
{
	char	*dollar;
	int		i;

	dollar = malloc(sizeof(char) * size);
	if (!dollar)
		return (NULL);
	i = 0;
	while (line[++i] && i < size)
		dollar[i - 1] = line[i];
	dollar[i - 1] = '\0';
	return (dollar);
}
