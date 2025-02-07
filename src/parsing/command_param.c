#include "../../include/minishell.h"

static int	count_args(t_data *data, t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	if (tmp->type == CMD || (tmp->type == ARG && \
		tmp->prev != data->token->prev && tmp->prev->type > 5))
		count ++;
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if (tmp->type == CMD || (tmp->type == ARG && \
		tmp->prev != data->token->prev && tmp->prev->type > 5))
			count ++;
		tmp = tmp->next;
	}
	return (count);
}

static int	add_to_command_param(char **command_param, int *i, char *str)
{
	command_param[*i] = ft_strdup(str);
	if (!command_param[*i])
		return (0);
	(*i)++;
	return (1);
}

static void	*free_command_param(char **cmd, int i)
{
	while (--i != -1)
		free(cmd[i]);
	free(cmd);
	return (NULL);
}

char	**get_param(t_data *data, t_token *token)
{
	char	**command_param;
	int		i;
	t_token	*tmp;

	i = 0;
	command_param = malloc(sizeof(char *) * (count_args(data, token) + 1));
	if (command_param == NULL)
		return (NULL);
	tmp = token;
	if (tmp->type != PIPE && (tmp->type == CMD || (tmp->type == ARG && \
		tmp->prev != data->token->prev && tmp->prev->type > 5)) && \
		!add_to_command_param(command_param, &i, tmp->str))
		return (free_command_param(command_param, i));
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if ((tmp->type == CMD || (tmp->type == ARG && \
			tmp->prev != data->token->prev && tmp->prev->type > 5)) && \
			!add_to_command_param(command_param, &i, tmp->str))
			return (free_command_param(command_param, i));
		tmp = tmp->next;
	}
	command_param[i] = NULL;
	return (command_param);
}
