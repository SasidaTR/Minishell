/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:39:57 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:39:58 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void	error_malloc(void)
{
	print_error(ERR_MALLOC);
	return ;
}

static void	update_oldpwd(t_data *data)
{
	t_list	*temp;
	char	*test;
	int		len;

	temp = data->env;
	test = NULL;
	len = len_list(temp);
	while (len--)
	{
		if (ft_strncmp(temp->str, "PWD=", 3) == 0)
			test = temp->str;
		temp = temp->next;
	}
	if (!test)
		export("OLDPWD", &data->env);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (error_malloc());
		export(test, &data->env);
	}
	free(test);
}

static void	update_pwd(t_data *data, char *param)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(data);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export(pwd, &data->env);
	free(pwd);
}

int	ft_cd(t_data *data, char **params)
{
	int	res;

	if (count_arg(params) == 2)
	{
		res = chdir(params[1]);
		if (res == 0)
			update_pwd(data, params[1]);
		if (res == -1)
			res *= -1;
		if (res == 1)
			perror(params[1]);
		return (res);
	}
	else if (count_arg(params) > 2)
		print_error(" too many arguments\n");
	return (1);
}
