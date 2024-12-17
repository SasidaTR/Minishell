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

void initialize(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
}

int main(int argc, char **argv, char **env)
{
	char    *command;
	char    **pipe_commands;
	char    **splited_command;
	char    *parsed_arg;

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
		pipe_commands = ft_split(command, '|');
		if (!pipe_commands || !pipe_commands[0])
		{
			free(command);
			free_array(pipe_commands);
			continue;
		}
		for (int i = 0; pipe_commands[i]; i++)
		{
			splited_command = ft_split(pipe_commands[i], ' ');
			if (!splited_command || !splited_command[0])
			{
				free_array(splited_command);
				continue;
			}
			for (int j = 0; splited_command[j]; j++)
			{
				parsed_arg = quotes(splited_command[j]);
				if (!parsed_arg)
				{
					printf("Error: Unclosed quotes\n");
					free_array(splited_command);
					splited_command = NULL;
					break;
				}
				free(splited_command[j]);
				splited_command[j] = parsed_arg;
			}
			if (!splited_command)
				continue;
			execute_command(splited_command, env);
			free_array(splited_command);
		}
		free(command);
		free_array(pipe_commands);
	}
	return (0);
}