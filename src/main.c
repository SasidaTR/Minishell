#include "../include/minishell.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
		return (true);
	return (false);
}

bool	is_empty(char *command)
{
	int	i;

	i = 0;
	while (command[i] && is_space(command[i]))
		i++;
	if (i == ft_strlen(command))
		return (true);
	return (false);
}

void	initialize(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	initialize_signals();
}

int	main(int argc, char **argv, char **env)
{
	// t_data data;
	char	*command;

	initialize(argc, argv, env);
	// make env
	while (1)
	{
		command = readline("minishell> ");
		if(!command) //pour gérer le ctrl+D sinon segfault
		{
			printf("exit\n");
			break;
		}
		if (is_empty(command))
			continue ;
		else
		{
			add_history(command);
		}
		// parsing
        exec_command(command);
		printf("%s\n", command); // to delete
	}
	//rl_clear_history();
	free(command);
	return (0);
}