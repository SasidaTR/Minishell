
#include "../../include/minishell.h"

void exec_command(char *command)
{
    pid_t pid;
    int status;
    char *args[2];

    pid = fork();
    if(pid == 0)
    {
        args[0] = command;
        args[1] = NULL;
        if(execve(command, args, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if(pid > 0)
    {
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("fork");
    }
}