#ifndef MINISHELL_H
# define MINISHELL_H
#define _XOPEN_SOURCE 700 //pour supp l'erreur dans handle.c

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
void exec_command(char **args, char **env);
char	**ft_split(char *str, char c);
void	free_array(char **array);
int ft_echo(void);
int	ft_strncmp(const char *s1, const char *s2, size_t n);


#endif