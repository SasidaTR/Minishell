
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
	// t_data data;
	char	*command;
	char	**args;

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
		{
			free(command);
			continue ;
		}
		add_history(command);
		args = ft_split(command, ' ');
		//print_args(args); // Inspecte le contenu de args
		free(command);
		if(!args || !args[0])
		{
			free_array(args);
			continue;
		}
		// parsing
		// for (int i = 0; args[i]; i++)
    	// 	printf("args[%d]: %s\n", i, args[i]);

        exec_command(args, env); //à modifier quand on aura récupéré notre propre env
		// printf("%s\n", command); // to delete
		free_array(args);
	}
	//rl_clear_history();
	// free(command);
	return (0);
}