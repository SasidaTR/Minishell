#include "../../include/minishell.h"

int	is_builtin(t_command *commands, t_data *data)
{
	if (ft_strncmp(commands->split_command[0], "echo", ft_strlen(commands->split_command[0])) == 0)
		return (ft_echo(commands), 1);
	else if (ft_strncmp(commands->split_command[0], "cd", ft_strlen(commands->split_command[0])) == 0)
		return (ft_cd(commands), 1);
	else if (ft_strncmp(commands->split_command[0], "pwd", ft_strlen(commands->split_command[0])) == 0)
		return (ft_pwd(data), 1);
	else if (ft_strncmp(commands->split_command[0], "export", ft_strlen(commands->split_command[0])) == 0)
		return (ft_export(commands, data), 1);
	else if (ft_strncmp(commands->split_command[0], "unset", ft_strlen(commands->split_command[0])) == 0)
		return (ft_unset(), 1);
	else if (ft_strncmp(commands->split_command[0], "env", ft_strlen(commands->split_command[0])) == 0)
		return (ft_env(data), 1);
	else if (ft_strncmp(commands->split_command[0], "exit", ft_strlen(commands->split_command[0])) == 0)
		return (ft_exit(commands, data), 1);
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
		if (is_builtin(commands, data))
		{
			i++;
			continue;
		} 
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
