#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**env;
}			t_data;

// built_ins
int		ft_echo(char **args);
int		ft_cd(void);
int		ft_pwd(void);
int		ft_export(void);
int		ft_unset(void);
int		ft_env(void);
int		ft_exit(void);

// handle
void	handle_sigint(int sig);

// execute
void	execute_command(char **args, char **env);

// libft
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(char *str, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
bool	is_empty(char *command);
bool	is_space(char c);

// parsing
bool	parsing(char *command, char **env);
char	*quotes(char *command);
char	**advanced_split(char *command, char sep);

// utils
void	free_array(char **array);
void	free_all(char *command, int exit_program);

#endif