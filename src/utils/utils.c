#include "../../include/minishell.h"

int	is_special(char *str)
{
	if (str && *str && ft_strlen(str) >= 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(str, ">>", 2))
			return (APPEND);
	}
	if (*str && ft_strlen(str) >= 1)
	{
		if (!ft_strncmp(str, "<", 1))
			return (INPUT);
		if (!ft_strncmp(str, ">", 1))
			return (TRUNC);
		if (!ft_strncmp(str, "|", 1))
			return (PIPE);
	}
	return (0);
}

bool	check_pipe(t_data *data)
{
	if (data->token->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		free_token(&data->token);
		free_command(&data->commands);
		return (false);
	}
	return (true);
}

void	absolute_path(char **path, char *command, t_data *data)
{
	*path = ft_strdup(command);
	if (!(*path))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (access((*path), F_OK))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, " : No such file or directory\n", ft_strlen(" : No such file or directory"));
		free(*path);
		*path = NULL;
	}
}

void	reset_sigquit(void)
{
	signal(SIGQUIT, SIG_DFL);
}
