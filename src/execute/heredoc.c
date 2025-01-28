# include "../../include/minishell.h"

// int handle_heredoc(char *delimiter)
// {
//     int pipe_fd[2];
//     char *line;

//     if(pipe(pipe_fd) == -1)
//     {
//         perror("pipe");
//         return(-1);
//     }
//     while(1)
//     {
//         printf("heredoc> ");
//         // line = get_next_line(STDIN_FILENO);
//         if(!line)
//             break;
//         if(ft_strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\n')
//         {
//             free(line);
//             break;
//         }
//         write(pipe_fd[1], line, strlen(line));
//         free(line);
//     }
//     close(pipe_fd[1]);
//     return(pipe_fd[0]);
// }