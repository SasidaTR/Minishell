
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

// void print_args(char **args)
// {
//     if (!args)
//     {
//         printf("args is NULL\n");
//         return;
//     }
//     for (int i = 0; args[i]; i++)
// 	{
//         printf("args[%d]: '%s'\n", i, args[i]);
//     	printf("args[%d]: NULL\n", i);
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	char	*command;
	char	**args;
	char	*parsed_arg;

	initialize(argc, argv, env);
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
		exec_command(args, env);
		free_array(args);
	}
	return (0);
}