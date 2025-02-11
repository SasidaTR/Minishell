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

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	char	path[PATH_MAX];
	char	*temp;
	int		i;

	if (!(*env))
	{
		temp = ft_strdup("OLDPWD");
		if (!temp || !append(&(data->env), temp) || getcwd(path, PATH_MAX) == NULL)
			free_all(data, ERR_MALLOC, EXT_MALLOC);
		temp = ft_strjoin("PWD=", path);
		if (!temp || !append(&(data->env), temp))
			free_all(data, ERR_MALLOC, EXT_MALLOC);
		return (1);
	}
	i = -1;
	list = NULL;
	while (env[++i])
	{
		temp = ft_strdup(env[i]);
		if (!temp || !append(&list, temp))
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
		g_signal_pid = 0;
	}
	rl_clear_history();
	free_all(&data, NULL, -1);
	return (0);
}
