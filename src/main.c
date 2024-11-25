#include "../include/minishell.h"

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
	while (1)
	{
		command = readline("minishell> ");
		printf("%s\n", command);
	}
}