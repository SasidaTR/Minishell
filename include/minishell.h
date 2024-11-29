#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// typedef struct s_data
// {

// }				t_data;

int	ft_strlen(char *str);
void	*ft_memset(void *s, int c, size_t n);
void initialize_signals(void);
void handle_sigint(int sig);
void exec_command(char *command);


#endif