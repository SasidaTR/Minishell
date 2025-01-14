#include "../../include/minishell.h"

bool parsing(t_command *commands)
{
	int i = 0;

	commands->pipeline = split_pipes(commands->command);
	if (!commands->pipeline)
		return (false);
	while (commands->pipeline[i])
	{
		char *cleaned_command = remove_quotes(commands->pipeline[i]);
		if (!cleaned_command)
		{
			free_array(commands->pipeline);
			return (false);
		}
		free(commands->pipeline[i]);
		commands->pipeline[i] = cleaned_command;
		i++;
	}
	return (true);
}
