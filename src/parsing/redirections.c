#include "../../include/minishell.h"

void	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("Minishell");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("Minishell");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

char	*extract_filename(char *command, int *index)
{
	int	start;
	int	len;

	start = *index;
	len = 0;
	while (command[*index] && command[*index] != ' ' && command[*index] != '<' && command[*index] != '>')
	{
		(*index)++;
		len++;
	}
	return (ft_substr(command, start, len));
}

bool	process_redirection(char *command, int *index)
{
	int		i;
	char	*filename;

	i = *index + 1;
	while (command[i] == ' ')
		i++;
	if (command[i] == '\0')
		return (false);
	filename = extract_filename(command, &i);
	if (!filename)
		return (false);
	if (command[*index] == '<')
		open_input_file(filename);
	else if (command[*index] == '>')
		open_output_file(filename);
	free(filename);
	*index = i - 1;
	return (true);
}

bool	handle_redirections(char *command)
{
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	while (command[i])
	{
		update_quote_state(command[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote)
		{
			if (command[i] == '<' || command[i] == '>')
			{
				if (!process_redirection(command, &i))
					return (false);
			}
		}
		i++;
	}
	return (true);
}
