#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE	1

# define INPUT			1	//"<"
# define HEREDOC		2	//"<<"
# define TRUNC			3	//">"
# define APPEND			4	//">>"
# define PIPE			5	//"|"
# define CMD			6	//"|"
# define ARG			7	//"|"

# define ERR_MALLOC		"malloc error\n"
# define ERR_PIPE		"pipe error\n"
# define ERR_FORK		"fork error\n"

# define EXT_MALLOC		1
# define EXT_PIPE		1
# define EXT_FORK		1

extern pid_t	g_signal_pid;

typedef struct s_command
{
	bool				skip_cmd;
	int					infile;
	int					outfile;
	char				**command_param;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	t_list			*env;
	t_token			*token;
	t_command		*commands;
	int				exit_code;
	int				pip[2];
	bool			sq;
}					t_data;

typedef struct s_list_gnl
{
	char				*content;
	struct s_list_gnl	*next;
	struct s_list_gnl	*prev;
}					t_list_gnl;

// libft
int		ft_atoi(const char *nptr);
void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

// Get_next_line
int		free_list_gnl(t_list_gnl **list);
int		how_many(t_list_gnl *list, char **line);
int		make_line(t_list_gnl *list, char **line);
int		new_line(t_list_gnl *list);
int		add_to_list_gnl(t_list_gnl **list, char *buf);
int		write_in_list_gnl(int fd, t_list_gnl **list);
int		clear_list_gnl(t_list_gnl **list);
char	*get_next_line(int fd);

// built_ins
int		ft_cd(t_data *data, char **params);
int		ft_echo(char **args);
int		ft_env(t_list	*env);
void	ft_exit(t_data *data, char **args);
int		ft_export(char **str, t_list **env);
bool	export(char *str, t_list **env);
int		ft_pwd(void);
int		ft_unset(char **str, t_list **env);

// execute
bool	execute(t_data *data);
bool	is_builtin(char *command);
void	child_process(t_data *data, t_command *commands, int *pip);
bool	run_builtin(t_data *data, t_command *commands);
char	*find_command(t_data *data, char *sample, t_list *env);
int		here_doc(t_data *data, char *word);

// parsing
bool	parsing(t_data *data, char *line);
void	quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);
int		exist_in_env(char *line, int *i, t_data *data);
char	*get_elem_env(t_list *env, char *key);
char	*get_dollar_word(char *line, int size);
int		add_dollar(char *line, int *index, char **str, t_data *data);
int		add_char(char *c, char **str, t_data *data, int *index);
int		replace_dollar(char **line, t_data *data);
char	**get_param(t_data *data, t_token *token);
bool	create_list_command(t_data *data);
bool	get_infile(t_data *data, t_token *token, t_command *cmd);
bool	get_outfile(t_token *token, t_command *command, t_data *data);
bool	create_list_token(t_token **begin, char *command);

// utils
int		free_list(t_list **list);
int		append(t_list **list, char *elem);
size_t	len_list(t_list *list);
void	clear_rl_line(void);
void	signals(void);
void	reset_sigquit(void);
int		append_command(t_command **list, int infile, int outfile, char **command_param);
void	free_command(t_command **list);
size_t	len_command(t_command *list);
char	**lst_to_arr(t_list *env);
void	sort_array(char **arr, int len);
void	free_array(char **arr);
bool	print_error(char *str);
void	free_all(t_data *data, char *err, int ext);
bool	print_error_token(t_token *token, t_data *data);
int		is_special(char *str);
bool	check_pipe(t_data *data);
void	absolute_path(char **path, char *cmd, t_data *data);
int		append_token(t_token **list, char *str, int type);
void	free_token(t_token **list);

#endif
