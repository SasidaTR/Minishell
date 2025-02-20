/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:41:23 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:41:43 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	syntax(char *str)
{
	int	i;

	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	exist(char *str, t_list *env)
{
	int		i;
	int		j;
	t_list	*temp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	j = 0;
	temp = env;
	if (!ft_strncmp(temp->str, str, i))
		return (j);
	temp = temp->next;
	j++;
	while (temp != env)
	{
		if (!ft_strncmp(temp->str, str, i))
			return (j);
		temp = temp->next;
		j++;
	}
	return (-1);
}

static void	check_env(t_list *temp, t_list **env)
{
	if (temp == (*env))
		(*env) = temp->next;
	if (temp->next == temp)
		(*env) = NULL;
}

static bool	unset(char *str, t_list **env)
{
	int		pos;
	int		i;
	t_list	*temp;

	if (!str || !(*str))
		return (false);
	if (!syntax(str))
	{
		print_error("unset: not a valid identifier\n");
		return (true);
	}
	pos = exist(str, (*env));
	if (pos == -1)
		return (false);
	temp = (*env);
	i = 0;
	while (i++ < pos)
		temp = temp->next;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp->str);
	check_env(temp, env);
	free(temp);
	temp = NULL;
	return (false);
}

int	ft_unset(char **str, t_list **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (str[i])
	{
		if (unset(str[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
