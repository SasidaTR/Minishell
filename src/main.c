#include "../include/minishell.h"

void	initialize(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
}

int loop()
{
	char *command;
	while (1)
	{
		command = readline("minishell> ");
		printf("%s\n", command);
	}
}

int	main(int argc, char **argv, char **env)
{
	// t_data data;

	initialize(argc, argv, env);
	return(loop());
}