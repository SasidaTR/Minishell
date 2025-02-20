/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:44:59 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:45:00 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_file(t_data *data, char *filename, int type)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = here_doc(data, filename);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}

static bool	get_in(t_data *data, t_token *temp, t_command *command)
{
	if (temp->type == INPUT)
	{
		if (command->infile >= 0)
			close(command->infile);
		if (temp == temp->next || temp->next->type <= 5)
			return (print_error_token(temp, data));
		command->infile = open_file(data, temp->next->str, INPUT);
		if (command->infile == -1)
			return (false);
	}
	else if (temp->type == HEREDOC)
	{
		if (command->infile >= 0)
			close(command->infile);
		if (temp == temp->next || temp->next->type <= 5)
			return (print_error_token(temp, data));
		command->infile = open_file(data, temp->next->str, HEREDOC);
		if (command->infile == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_data *data, t_token *token, t_command *command)
{
	t_token	*temp;

	temp = token;
	if (temp->type != PIPE && !get_in(data, temp, command))
		return (false);
	if (temp->type == PIPE)
		return (true);
	temp = temp->next;
	while (temp->type != PIPE && temp != data->token)
	{
		if (!get_in(data, temp, command))
			return (false);
		temp = temp->next;
	}
	return (true);
}

static bool	get_out(t_token *temp, t_command *command, t_data *data)
{
	if (temp->type == TRUNC)
	{
		if (command->outfile >= 0)
			close(command->outfile);
		if (temp == temp->next || temp->next->type <= 5)
			return (print_error_token(temp, data));
		command->outfile = open_file(NULL, temp->next->str, TRUNC);
		if (command->outfile == -1)
			return (false);
	}
	else if (temp->type == APPEND)
	{
		if (command->outfile >= 0)
			close(command->outfile);
		if (temp == temp->next || temp->next->type <= 5)
			return (print_error_token(temp, data));
		command->outfile = open_file(NULL, temp->next->str, APPEND);
		if (command->outfile == -1)
			return (false);
	}
	return (true);
}

bool	get_outfile(t_token *token, t_command *command, t_data *data)
{
	t_token	*temp;

	temp = token;
	if (temp->type != PIPE && !get_out(temp, command, data))
		return (false);
	temp = temp->next;
	while (temp != data->token && temp->type != PIPE)
	{
		if (!get_out(temp, command, data))
			return (false);
		temp = temp->next;
	}
	return (true);
}
