/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:11:11 by earnera           #+#    #+#             */
/*   Updated: 2024/12/12 14:27:41 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void exec_command(char **args, char **env)
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
			waitpid(pid, &status, 0); // si pid!=0 alors c'est le père donc il attend le fils
		}
		else
		{
			perror("fork");
		}
	}
}

void	exec_pipe(char **args, char **env, int is_first, int is_last)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!is_last && pipe(pipe_fd) == -1)
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
	if (pid == 0) // Processus enfant
	{
		if (!is_first)
			dup2(pipe_fd[0], STDIN_FILENO);
		if (!is_last)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (execve(args[0], args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else // Processus parent
	{
		waitpid(pid, NULL, 0);
		if (!is_last)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
	}
}

// void exec_command(char *command)
// {
// 	pid_t pid;
// 	int status;
// 	char *args[2];

// 	pid = fork();
// 	if(pid == 0)
// 	{
// 		args[0] = command;
// 		args[1] = NULL;
// 		if(execve(command, args, NULL) == -1)
// 		{
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if(pid > 0)
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	else
// 	{
// 		perror("fork");
// 	}
// }