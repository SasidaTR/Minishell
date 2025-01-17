#include "../../include/minishell.h"

int is_builtin(t_command *commands, t_data *data)
{
	if (ft_strncmp(commands->split_command[0], "echo", ft_strlen(commands->split_command[0])) == 0)
		return (ft_echo(commands), 1);
	else if (ft_strncmp(commands->split_command[0], "cd", ft_strlen(commands->split_command[0])) == 0)
		return (ft_cd(commands, data), 1);
	else if (ft_strncmp(commands->split_command[0], "pwd", ft_strlen(commands->split_command[0])) == 0)
		return (ft_pwd(data), 1);
	else if (ft_strncmp(commands->split_command[0], "export", ft_strlen(commands->split_command[0])) == 0)
		return (ft_export(commands, data), 1);
	else if (ft_strncmp(commands->split_command[0], "unset", ft_strlen(commands->split_command[0])) == 0)
		return (ft_unset(commands, data), 1);
	else if (ft_strncmp(commands->split_command[0], "env", ft_strlen(commands->split_command[0])) == 0)
		return (ft_env(commands, data), 1);
	else if (ft_strncmp(commands->split_command[0], "exit", ft_strlen(commands->split_command[0])) == 0)
		return (ft_exit(commands, data), 1);
	return (0);
}

void execute_command(t_command *commands, char **env, t_data *data)
{
	int i;
	pid_t pid;
	int pipe_fd[2];
	int status;
	int in_fd = 0;
	char *cmd_path;

	i = 0;
	while (commands->pipeline[i])
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		commands->split_command = ft_split(commands->pipeline[i], ' ');
		if (is_builtin(commands, data))
		{
			free(commands->split_command);
			return;
		}
		pid = fork();
		if (pid == 0)
		{
			dup2(in_fd, STDIN_FILENO);
			if (commands->pipeline[i + 1])
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (!cmd_exist(&cmd_path, commands->split_command[0], env))
			{
				ft_putstr_fd("Command not found: ", STDERR_FILENO);
				ft_putendl_fd(commands->split_command[0], STDERR_FILENO);
				free_array(commands->split_command);
				exit(127); // Command not found error
			}
			if (setup_redirections(commands->split_command) < 0)
			{
				perror("redirection");
				exit(EXIT_FAILURE);
			}
			execve(cmd_path, commands->split_command, env);
			perror("execve");
			free(cmd_path);
			free_array(commands->split_command);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			close(pipe_fd[1]);
			in_fd = pipe_fd[0];
		}
		else
			perror("fork");
		i++;
	}
	close(in_fd);
}
