/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:45:05 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:45:05 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	handle_infile(t_data *data, t_token *temp)
{
	if (!get_infile(data, temp, data->commands->prev)
		&& data->commands->prev->infile != -1)
		return (false);
	if (data->commands->prev->infile == -1)
	{
		data->commands->prev->skip_cmd = true;
		data->commands->prev->outfile = -1;
		data->exit_code = 1;
		return (true);
	}
	return (true);
}

static bool	handle_outfile(t_data *data, t_token *temp)
{
	if (!get_outfile(temp, data->commands->prev, data)
		&& data->commands->prev->outfile != -1)
		return (false);
	if (data->commands->prev->outfile == -1)
	{
		if (data->commands->prev->infile >= 0)
			close(data->commands->prev->infile);
		data->commands->prev->skip_cmd = true;
		data->commands->prev->infile = -1;
		data->exit_code = 1;
		return (true);
	}
	return (true);
}

static bool	fill_command(t_data *data, t_token *temp)
{
	if (!handle_infile(data, temp))
		return (false);
	if (!handle_outfile(data, temp))
		return (false);
	data->commands->prev->command_param = get_param(data, temp);
	if (!data->commands->prev->command_param)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (true);
}

static bool	norm(t_data *data, t_token *temp)
{
	if (!append_command(&data->commands, -2, -2, NULL))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (!fill_command(data, temp))
	{
		if (data->exit_code == 0)
			data->exit_code = 1;
		return (false);
	}
	return (true);
}

bool	create_list_command(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	if (!norm(data, temp))
		return (false);
	temp = temp->next;
	while (temp != data->token)
	{
		if (temp->prev->type == PIPE)
		{
			if (!norm(data, temp))
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}
