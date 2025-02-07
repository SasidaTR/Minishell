#include "../include/minishell.h"

pid_t	g_signal_pid;

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

bool	parsing(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		free(line);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	free(line);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		free_token(&data->token);
		return (false);
	}
	if (!data->token || !create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->commands);
		return (false);
	}
	return (check_pipe(data));
}

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	char	path[PATH_MAX];
	char	*tmp;
	int		i;

	if (!(*env))
	{
		tmp = ft_strdup("OLDPWD");
		if (!tmp || !append(&(data->env), tmp) || getcwd(path, PATH_MAX) == NULL)
			free_all(data, ERR_MALLOC, EXT_MALLOC);
		tmp = ft_strjoin("PWD=", path);
		if (!tmp || !append(&(data->env), tmp))
			free_all(data, ERR_MALLOC, EXT_MALLOC);
		return (1);
	}
	i = -1;
	list = NULL;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp || !append(&list, tmp))
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
	g_signal_pid = 0;
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
		command = readline("minishell> ");
		if (!command)
			free_all(&data, "exit\n", data.exit_code);
		if (empty_line(command))
			continue ;
		add_history(command);
		if (!parsing(&data, command))
			continue ;
		if (!execute(&data))
			free_all(&data, ERR_PIPE, EXT_PIPE);
		free_cmd(&data.commands);
		free_token(&data.token);
		g_signal_pid = 0;
	}
	rl_clear_history();
	free_all(&data, NULL, -1);
	return (0);
}
