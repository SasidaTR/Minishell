#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# define INT_MAX 2147483647

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	char	***commandss;
	char	**commands;
	char	**split_command;
	char	*command;
}			t_command;

typedef struct s_data
{
	char	**env;
}			t_data;

// built_ins
int		ft_echo(char **split_command);
int		ft_cd(char **split_command);
int		ft_pwd(t_data *data);
int		ft_export(char **split_command, t_data *data);
int		ft_unset(void);
int		ft_env(t_data *data);
int		ft_exit(void);

// handle
void	handle_sigint(int sig);

// execute
void	execute_command(t_command *commands, char **env, t_data *data);

// libft
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(char *str, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
bool	is_empty(char *command);
bool	is_space(char c);

// parsing
bool	parsing(t_command *commands, char **env, t_data *data);
char	**advanced_split(char *command, char sep);
bool	handle_redirections(t_command *command);
char	*remove_quotes(char *str);

// utils
void	free_array(char **array);
void	free_all(t_command *commands, int exit_program);
void	sort_array(char **array, int n);
int		count_array(char **array);


#endif