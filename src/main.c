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
		if (is_empty(command))
			continue ;
		printf("%s\n", command); // to delete
		// create history
		// parsing
		// execution
	}
	// rl_clear_history();
	// free
	return (0);
}