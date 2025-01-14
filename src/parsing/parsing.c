#include "../../include/minishell.h"

bool	parsing(t_command *commands)
{
	int		i;
	char	*cleaned_command;

	commands->pipeline = split_pipes(commands->command);
	if (!commands->pipeline)
		return (false);
	i = 0;
	while (commands->pipeline[i])
	{
		cleaned_command = remove_quotes(commands->pipeline[i]);
		if (!cleaned_command)
		{
			free_array(commands->pipeline);
			return (false);
		}
		free(commands->pipeline[i]);
		commands->pipeline[i] = cleaned_command;
		if (!handle_redirections(commands->pipeline[i]))
		{
			free_array(commands->pipeline);
			return (false);
		}
		i++;
	}
	return (true);
}
