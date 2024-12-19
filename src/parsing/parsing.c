#include "../../include/minishell.h"

void	parsing(char *command, char **env)
{
	char	**pipe_commands;
	char	**splited_command;
	char	*parsed_arg;

	pipe_commands = advanced_split(command, '|');
	if (!pipe_commands || !pipe_commands[0])
	{
		free(command);
		free_array(pipe_commands);
		return ;
	}
	for (int i = 0; pipe_commands[i]; i++)
	{
		splited_command = advanced_split(pipe_commands[i], ' ');
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
				break;
			}
			free(splited_command[j]);
			splited_command[j] = parsed_arg;
		}
		if (splited_command)
			execute_command(splited_command, env);
		free_array(splited_command);
	}
	free_array(pipe_commands);
}