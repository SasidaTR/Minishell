#include "../include/minishell.h"
int get_env(t_data *data, char **env)
{
    int i = 0;

    if (!env)
        return (0);
    while (env[i])
        i++;
    data->env = (char**)malloc(sizeof(char *) * (i + 1));
    if (!data->env)
        return (0);
    i = 0;
    while (env[i])
    {
        data->env[i] = ft_strdup(env[i]);
        if (!data->env[i])
        {
            free_array(data->env);
            return (0);
        }
        i++;
    }
    data->env[i] = 0;
    data->env_size = i;
    return (1);
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
	data->exit_code = 0;
	data->env_size = 0;
}

int main(int argc, char **argv, char **env)
{
	t_data data;
	t_command commands;

	initialize(argc, argv, &data);
	if (!get_env(&data, env))
		return (0);
	initialize_signals();
	while (1)
	{
		commands.command = readline("Minishell> ");
		if (!commands.command)
		{
			free_array(data.env);
			free(commands.command);
			exit(1);
		}
		if (is_empty(commands.command))
			continue;
		add_history(commands.command);
		if (!parsing(&commands))
		{
			free(commands.command);
			continue;
		}
		execute_command(&commands, env, &data);
		free(commands.command);
	}
	free(commands.command);
	free_array(data.env);
	return (0);
}
