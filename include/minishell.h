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
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	char	**pipeline;
	char	**split_command;
	char	*command;
}			t_command;

typedef struct s_data
{
	char	**env;
	int		exit_code;
	int		env_size;
}			t_data;

// built_ins
int		ft_echo(t_command *commands);
int		ft_cd(t_command *commands, t_data *data);
int		ft_pwd(t_data *data);
int		ft_export(t_command *commands, t_data *data);
int		ft_unset(void);
int		ft_env(t_data *data);
int		ft_exit(t_command *commands, t_data *data);

// handle
void	handle_sigint(int sig);

// execute
void	execute_command(t_command *commands, char **env, t_data *data);

// libft
int		count_args(char **array);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar(char c);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	**ft_split(char *str, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
bool	is_empty(char *command);
bool	is_space(char c);

// parsing
bool	parsing(t_command *commands);
char	**split_pipes(char *command);
bool	update_quote_state(char c, bool *in_single_quote, bool *in_double_quote);
char	*remove_quotes(char *str);
int		setup_redirections(char **cmd);

// utils
void	free_array(char **array);
void	sort_array(char **array, int n);
void	remove_elements_from_array(char **array, int index, int count);

#endif