#include "../include/minishell.h"

void	initialize_signals(void)
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

	initialize(argc, argv, env);
	initialize_signals();
	while (1)
	{
		command = readline("minishell> ");
		if (!command)
		{
			perror("readline");
			printf("exit\n");
			break;
		}
		if (is_empty(command))
		{
			free(command);
			continue;
		}
		add_history(command);
		parsing(command, env);
		free(command);
	}
	return (0);
}