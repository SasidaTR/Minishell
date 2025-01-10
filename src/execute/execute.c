#include "../../include/minishell.h"

int	is_builtin(char **split_command, t_data *data)
{
	if (ft_strncmp(split_command[0], "echo", ft_strlen(split_command[0])) == 0)
		return (ft_echo(split_command), 1);
	else if (ft_strncmp(split_command[0], "cd", ft_strlen(split_command[0])) == 0)
		return (ft_cd(split_command), 1);
	else if (ft_strncmp(split_command[0], "pwd", ft_strlen(split_command[0])) == 0)
		return (ft_pwd(data), 1);
	else if (ft_strncmp(split_command[0], "export", ft_strlen(split_command[0])) == 0)
		return (ft_export(split_command, data), 1);
	else if (ft_strncmp(split_command[0], "unset", ft_strlen(split_command[0])) == 0)
		return (ft_unset(), 1);
	else if (ft_strncmp(split_command[0], "env", ft_strlen(split_command[0])) == 0)
		return (ft_env(data), 1);
	else if (ft_strncmp(split_command[0], "exit", ft_strlen(split_command[0])) == 0)
		return (ft_exit(), 1);
	return (0);
}

void	execute_command(t_command *commands, char **env, t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (commands->commands[i])
	{
		if (is_builtin(&commands->split_command[i], data))
			return ;
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(commands->split_command[i], commands->split_command, env) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid > 0)
				waitpid(pid, &status, 0);
			else
				perror("fork");
		}
		i++;
	}
}
