#include "../../include/minishell.h"

int	handle_heredoc_redirection(char **cmd, int *index)
{
	int		pipe_fd[2];
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	if (!cmd[*index + 1])
		return (-1);
	if (pipe(pipe_fd) < 0)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		if (getline(&line, &len, stdin) == -1)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!ft_strcmp(line, cmd[*index + 1]))
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
	}
	free(line);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	*index += 1;
	return (0);
}

int	handle_append_redirection(char **cmd, int *index)
{
	int	fd;

	if (!cmd[*index + 1])
		return (-1);
	fd = open(cmd[*index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (-1);
	}
	close(fd);
	*index += 1;
	return (0);
}

int	handle_output_redirection(char **cmd, int *index)
{
	int	fd;

	if (!cmd[*index + 1])
		return (-1);
	fd = open(cmd[*index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (-1);
	}
	close(fd);
	*index += 1;
	return (0);
}

int	handle_input_redirection(char **cmd, int *index)
{
	int	fd;

	if (!cmd[*index + 1])
		return (-1);
	fd = open(cmd[*index + 1], O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (-1);
	}
	close(fd);
	*index += 1;
	return (0);
}

int	setup_redirections(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "<"))
		{
			if (handle_input_redirection(cmd, &i) < 0)
				return (-1);
			remove_elements_from_array(cmd, i - 1, 2);
			i--;
		}
		else if (!ft_strcmp(cmd[i], ">"))
		{
			if (handle_output_redirection(cmd, &i) < 0)
				return (-1);
			remove_elements_from_array(cmd, i - 1, 2);
			i--;
		}
		else if (!ft_strcmp(cmd[i], ">>"))
		{
			if (handle_append_redirection(cmd, &i) < 0)
				return (-1);
			remove_elements_from_array(cmd, i - 1, 2);
			i--;
		}
		else if (!ft_strcmp(cmd[i], "<<"))
		{
			if (handle_heredoc_redirection(cmd, &i) < 0)
				return (-1);
			remove_elements_from_array(cmd, i - 1, 2);
			i--;
		}
		else
			i++;
	}
	return (0);
}
