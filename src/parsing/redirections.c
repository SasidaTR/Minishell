#include "../../include/minishell.h"

void	remove_redirection_tokens(t_command *commands, int index)
{
	free(commands->split_command[index]);
	free(commands->split_command[index + 1]);
	while (commands->split_command[index + 2])
	{
		commands->split_command[index] = commands->split_command[index + 2];
		index++;
	}
	commands->split_command[index] = NULL;
}

bool	handle_redirections(t_command *commands)
{
	int		fd;

	for (int i = 0; commands->split_command[i]; i++)
	{
		if (ft_strcmp(commands->split_command[i], "<") == 0)
		{
			fd = open(commands->split_command[i + 1], O_RDONLY);
			if (fd == -1)
			{
				perror("Error opening file");
				return (false);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			remove_redirection_tokens(commands, i);
			i--;
		}
		else if (ft_strcmp(commands->split_command[i], ">") == 0)
		{
			fd = open(commands->split_command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("Error opening file");
				return (false);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			remove_redirection_tokens(commands, i);
			i--;
		}
	}
	return (true);
}
