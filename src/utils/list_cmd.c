#include "../../include/minishell.h"

static int	command_new_elem(t_command **new, int infile, int outfile, char **command_param)
{
	(*new) = malloc(sizeof(t_command));
	if (*new == NULL)
		return (0);
	(*new)->skip_cmd = false;
	(*new)->infile = infile;
	(*new)->outfile = outfile;
	(*new)->command_param = command_param;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

int	append_command(t_command **list, int infile, int outfile, char **command_param)
{
	t_command	*new;

	if (!command_new_elem(&new, infile, outfile, command_param))
		return (0);
	if (!(*list))
	{
		(*list) = new;
		(*list)->prev = *list;
		(*list)->next = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

static void	free_all_command(t_command *temp)
{
	if (temp->infile > 0)
		close(temp->infile);
	temp->infile = -2;
	if (temp->outfile > 0)
		close(temp->outfile);
	temp->outfile = -2;
	free_array(temp->command_param);
}

void	free_command(t_command **list)
{
	t_command	*temp;
	t_command	*current;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		temp = current;
		current = current->next;
		free_all_command(temp);
		free(temp);
	}
	free_all_command(current);
	free(current);
	*list = NULL;
}

size_t	len_command(t_command *list)
{
	t_command	*temp;
	size_t	i;

	if ((list))
	{
		temp = list;
		i = 1;
		while (temp->next != list)
		{
			++i;
			temp = temp->next;
		}
		return (i);
	}
	return (0);
}
