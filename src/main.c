#include "../include/minishell.h"

int get_env(t_data *data, char **env)
{
	int i;
	
	i = 0;
	if(env == NULL)
		return(0);
	while(env[i])
		i++;
	if(!(data->env = (char**)malloc(sizeof(char *) * (i + 1))))
		return(0);
	i = 0;
	while(env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
	data->env[i] = 0;
	return(1);
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

void	initialize(int argc, char **argv, t_data *data)
{
	(void)argc;
	(void)argv;
	data->env = NULL;
}
// void print_env(t_data *data)
// {
// 	int i = 0;
// 	while(data->env[i])
// 	{
// 		printf("env = %s\n", data->env[i]);
// 		i++;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*command;

	initialize(argc, argv, &data);
	if (!get_env(&data, env))
		return (0); // libérer quand on aura des fonctions de free
	// print_env(&data);
	initialize_signals();
	while (1)
	{
		command = readline("Minishell> ");
		if (!command)
			free_all(command, 1);
		if (is_empty(command))
		{
			free(command);
			continue ;
		}
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
