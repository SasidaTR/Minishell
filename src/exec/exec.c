
#include "../../include/minishell.h"

int is_builtin(char **args)
{
    if(ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
        return(ft_echo());
    else if(ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
        return(ft_cd());
    else if(ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
        return(ft_pwd());
    else if(ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
        return(ft_export());
    else if(ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
        return(ft_unset());
    else if(ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
        return(ft_env());
    else if(ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
        return(ft_exit());
    return(0);

}

void exec_command(char **args, char **env)
{
    pid_t pid;
    int status;

    if(is_builtin(args[0]))
        return;
    else
    {
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