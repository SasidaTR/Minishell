#include "../include/minishell.h"

void initialize_signals(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	initialize(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
}

int	main(int argc, char **argv, char **env)
{
	char	*command;
	char	**args;
	char	*parsed_arg;

	initialize(argc, argv, env);
	initialize_signals();
	while (1)
	{
		command = readline("minishell> ");
		if (!command)
		{
			printf("exit\n");
			break;
		}
		if (is_empty(command))
		{
			free(command);
			continue;
		}
		add_history(command);
		args = ft_split(command, ' ');
		free(command);
		if (!args || !args[0])
		{
			free_array(args);
			continue;
		}
		for (int i = 0; args[i]; i++)
		{
			parsed_arg = quotes(args[i]);
			if (!parsed_arg)
			{
				printf("Error: Unclosed quotes\n");
				free_array(args);
				args = NULL;
				break;
			}
			free(args[i]);
			args[i] = parsed_arg;
		}
		if (!args)
			continue;
		if (ft_strchr(command, '|'))
			exec_pipes(command, env);
		else
			exec_command(args, env);
		free_array(args);
	}
	return (0);
}