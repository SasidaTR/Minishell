#include "../../include/minishell.h"

int is_builtin(char **splited_command)
{
	if (ft_strncmp(splited_command[0], "echo", ft_strlen(splited_command[0])) == 0)
		return (ft_echo(splited_command), 1);
	else if (ft_strncmp(splited_command[0], "cd", ft_strlen(splited_command[0])) == 0)
		return (ft_cd(), 1);
	else if (ft_strncmp(splited_command[0], "pwd", ft_strlen(splited_command[0])) == 0)
		return (ft_pwd(), 1);
	else if (ft_strncmp(splited_command[0], "export", ft_strlen(splited_command[0])) == 0)
		return (ft_export(), 1);
	else if (ft_strncmp(splited_command[0], "unset", ft_strlen(splited_command[0])) == 0)
		return (ft_unset(), 1);
	else if (ft_strncmp(splited_command[0], "env", ft_strlen(splited_command[0])) == 0)
		return (ft_env(), 1);
	else if (ft_strncmp(splited_command[0], "exit", ft_strlen(splited_command[0])) == 0)
		return (ft_exit(), 1);
	return (0);
}

void	execute_command(char **splited_command, char **env)
{
	pid_t pid;
	int status;

	if (is_builtin(&splited_command[0]))
		return ;
	else
	{
		pid = fork();
		if(pid == 0)
		{
			if(execve(splited_command[0], splited_command, env) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if(pid > 0)
			waitpid(pid, &status, 0);
		else
			perror("fork");
	}
}

