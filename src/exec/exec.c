
#include "../../include/minishell.h"

void exec_command(char **args, char **env)
{
    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0) //si c'est le fils
    {
        if(execve(args[0], args, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if(pid > 0)
    {
        waitpid(pid, &status, 0); //si pid!=0 alors c'est le père donc il attend le fils
    }
    else
    {
        perror("fork");
    }
}

// void exec_command(char *command)
// {
//     pid_t pid;
//     int status;
//     char *args[2];

//     pid = fork();
//     if(pid == 0)
//     {
//         args[0] = command;
//         args[1] = NULL;
//         if(execve(command, args, NULL) == -1)
//         {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else if(pid > 0)
//     {
//         waitpid(pid, &status, 0);
//     }
//     else
//     {
//         perror("fork");
//     }
// }