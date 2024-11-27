#include "../include/minishell.h"

void	initialize(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
}

void loop(void)
{
	char *command;
	while (1)
	{
		command = readline("minishell> ");
		if(!command)
		{
			printf("exit");
			break;
		}
		if(command)
		{
			add_history(command);
		}
		printf("%s\n", command);
		free(command);
	}
}

int	main(int argc, char **argv, char **env)
{
	// t_data data;

	initialize(argc, argv, env);
	loop();
	return(0);
}