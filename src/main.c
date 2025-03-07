/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:45:44 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:45:44 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	g_signal;

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	init_default_env(t_data *data)
{
	char	path[PATH_MAX];
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || !append(&(data->env), tmp) || getcwd(path, PATH_MAX) == NULL)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !append(&(data->env), tmp))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (1);
}

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	int		i;
	char	*tmp;

	if (!(*env))
		return (init_default_env(data));
	i = -1;
	list = NULL;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_list(&list));
		if (!append(&list, tmp))
			return (free_list(&list));
	}
	data->env = list;
	return (1);
}

void	init_data(int argc, char **argv, t_data *data)
{
	(void)argc;
	(void)argv;
	data->env = NULL;
	data->token = NULL;
	data->commands = NULL;
	data->exit_code = 0;
	data->pip[0] = -1;
	data->pip[1] = -1;
	g_signal = 0;
	signals();
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*command;

	init_data(argc, argv, &data);
	if (!make_env(&data, env))
		free_all(&data, ERR_MALLOC, EXT_MALLOC);
	while (1)
	{
		command = readline("mini> ");
		if (!command)
			free_all(&data, NULL, data.exit_code);
		if (empty_line(command))
			continue ;
		add_history(command);
		if (!parsing(&data, command))
			continue ;
		if (!execute(&data))
			free_all(&data, ERR_PIPE, EXT_PIPE);
		free_command(&data.commands);
		free_token(&data.token);
		g_signal = 0;
	}
	rl_clear_history();
	free_all(&data, NULL, -1);
	return (0);
}
