#include "../../include/minishell.h"

static int	in_env(t_data *data, char *line, int size, char **str)
{
	char	*temp;
	char	*key;
	char	*value;

	key = get_dollar_word(line, size);
	value = get_elem_env(data->env, key);
	if (key)
		free(key);
	temp = ft_strjoin(*str, value);
	if (value)
		free(value);
	free(*str);
	if (!temp)
		return (0);
	*str = temp;
	return (1);
}

static int	dollar_point_interrogation(t_data *data, char **str)
{
	char	*temp;
	char	*temp2;

	temp = ft_itoa(data->exit_code);
	if (!temp)
		return (0);
	temp2 = ft_strjoin(*str, temp);
	free(temp);
	free(*str);
	if (!temp2)
		return (0);
	*str = temp2;
	return (1);
}

int	add_char(char *c, char **str, t_data *data, int *index)
{
	char	char_to_str[2];
	char	*temp;
	int		i;

	i = 0;
	if (c[i] == '$' && !data->sq && exist_in_env(c, &i, data))
		return (1);
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	temp = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!temp)
		return (0);
	*str = temp;
	return (1);
}

int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int		ctrl;
	int		n;

	n = *index;
	ctrl = exist_in_env(line, index, data);
	if (ctrl == 1)
		return (in_env(data, &line[n], *index - n, str));
	else if (ctrl == 2)
	{
		(*index) += 2;
		return (dollar_point_interrogation(data, str));
	}
	else
	{
		++(*index);
		while (line[*index] && \
			(ft_isalnum(line[*index]) || line[*index] == '_'))
			++(*index);
		return (1);
	}
}

int	replace_dollar(char **line, t_data *data)
{
	bool	dq;
	int		i;
	char	*str;

	i = 0;
	dq = false;
	data->sq = false;
	str = ft_strdup("");
	while ((*line)[i])
	{
		quoting_choice(&dq, &data->sq, NULL, (*line)[i]);
		if ((*line)[i] == '$' && (*line)[i + 1] && ((*line)[i + 1] != '\'' &&
			(*line)[i + 1] != '"') && (ft_isalpha((*line)[i + 1]) ||
			(*line)[i + 1] == '?' || (*line)[i + 1] == '_') && !data->sq &&
			!add_dollar((*line), &i, &str, data))
			return (0);
		if ((*line)[i] && !add_char(&(*line)[i], &str, data, &i))
			return (0);
	}
	free(*line);
	*line = str;
	return (1);
}
