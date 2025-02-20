/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:46:25 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:46:26 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_args(t_data *data, t_token *token)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = token;
	if (temp->type == CMD || (temp->type == ARG && \
		temp->prev != data->token->prev && temp->prev->type > 5))
		count ++;
	temp = temp->next;
	while (temp != data->token && temp->type != PIPE)
	{
		if (temp->type == CMD || (temp->type == ARG && \
		temp->prev != data->token->prev && temp->prev->type > 5))
			count ++;
		temp = temp->next;
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
	t_token	*temp;

	i = 0;
	command_param = malloc(sizeof(char *) * (count_args(data, token) + 1));
	if (command_param == NULL)
		return (NULL);
	temp = token;
	if (temp->type != PIPE && (temp->type == CMD || (temp->type == ARG && \
		temp->prev != data->token->prev && temp->prev->type > 5)) && \
		!add_to_command_param(command_param, &i, temp->str))
		return (free_command_param(command_param, i));
	temp = temp->next;
	while (temp != data->token && temp->type != PIPE)
	{
		if ((temp->type == CMD || (temp->type == ARG && \
			temp->prev != data->token->prev && temp->prev->type > 5)) && \
			!add_to_command_param(command_param, &i, temp->str))
			return (free_command_param(command_param, i));
		temp = temp->next;
	}
	command_param[i] = NULL;
	return (command_param);
}
