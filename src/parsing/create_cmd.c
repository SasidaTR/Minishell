#include "../../include/minishell.h"

static bool	fill_cmd(t_data *data, t_token *tmp)
{
	if (!get_infile(data, tmp, data->commands->prev) && \
		data->commands->prev->infile != -1)
		return (false);
	if (data->commands->prev->infile == -1)
	{
		data->commands->prev->skip_cmd = true;
		data->commands->prev->outfile = -1;
		return (true);
	}
	if (!get_outfile(tmp, data->commands->prev, data) && data->commands->prev->outfile \
		!= -1)
		return (false);
	if (data->commands->prev->outfile == -1)
	{
		if (data->commands->prev->infile >= 0)
			close (data->commands->prev->infile);
		data->commands->prev->skip_cmd = true;
		data->commands->prev->infile = -1;
		return (true);
	}
	data->commands->prev->command_param = get_param(data, tmp);
	if (!data->commands->prev->command_param)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (true);
}

static bool	norm(t_data *data, t_token *tmp)
{
	if (!append_cmd(&data->commands, -2, -2, NULL))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (!fill_cmd(data, tmp))
	{
		data->exit_code = 2;
		return (false);
	}
	return (true);
}

bool	create_list_cmd(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!norm(data, tmp))
		return (false);
	tmp = tmp->next;
	while (tmp != data->token)
	{
		if (tmp->prev->type == PIPE)
		{
			if (!norm(data, tmp))
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
