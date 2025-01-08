#include "../include/minishell.h"

int	get_env(t_data *data, char **env)
{
	int		i;
	char	**temp_path;

	i = 0;
	if (env == NULL)
		return (0);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			temp_path = ft_split(env[i], '=');
			if (temp_path && temp_path[1])
			{
				data->env = ft_split(temp_path[1], ':');
				free_array(temp_path);
				return (1);
			}
			free_array(temp_path);
		}
		i++;
	}
	return (0);
}

void	initialize_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	initialize(t_data *data, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	data->env = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char	*command;
	t_data	data;

	initialize(&data, argc, argv, env);
	if (!get_env(&data, env))
		return (0); // libérer quand on aura des fonctions de free
	initialize_signals();
	while (1)
	{
		command = readline("Minishell> ");
		if (!command)
			free_all(command, 1);
		if (is_empty(command))
			continue ;
		add_history(command);
		if (!parsing(command, env))
			continue ;
		// if (!execute())
		// 	free_all(command, 1);
		free_all(command, 0);
	}
	free_array(data.env);
	return (0);
}
