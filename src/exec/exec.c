#include "../../include/minishell.h"

int is_builtin(char **args)
{
	if(ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return(ft_echo(args), 1);
	else if(ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return(ft_cd(), 1);
	else if(ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return(ft_pwd(), 1);
	else if(ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return(ft_export(), 1);
	else if(ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return(ft_unset(), 1);
	else if(ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return(ft_env(), 1);
	else if(ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return(ft_exit(), 1);
	return(0);

}

void	exec_command(char **args, char **env)
{
	pid_t pid;
	int status;

	if(is_builtin(&args[0]))
		return;
	else
	{
		pid = fork();
		if(pid == 0) // si c'est le fils
		{
			if(execve(args[0], args, env) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if(pid > 0)
		{
			waitpid(pid, &status, 0); // si pid != 0 alors c'est le père donc il attend le fils
		}
		else
		{
			perror("fork");
		}
	}
}

void exec_pipes(char *command, char **env)
{
	char	**commands = pipes(command);
	int		pipe_fd[2];
	int		prev_fd = -1;
	pid_t	pid;
	int		i = 0;

	while (commands && commands[i])
	{
		if (commands[i + 1] && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (commands[i + 1])
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			char **args = ft_split(commands[i], ' ');
			if (execve(args[0], args, env) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (commands[i + 1])
				close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	free_array(commands);
}
