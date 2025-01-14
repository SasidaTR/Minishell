#include "../../include/minishell.h"

void	update_env(t_data *data, const char *key, const char *value)
{
	int		i;
	size_t	key_len;
	size_t	value_len;
	char	*new_var;
	char	**new_env;

	if (!data || !key || !value)
		return ;
	key_len = strlen(key);
	value_len = strlen(value);
	new_var = malloc(key_len + value_len + 2);
	if (!new_var)
	{
		perror("malloc");
		return ;
	}
	ft_memcpy(new_var, key, key_len);
	new_var[key_len] = '=';
	ft_memcpy(new_var + key_len + 1, value, value_len);
	new_var[key_len + value_len + 1] = '\0';
	i = 0;
	while (data->env && data->env[i])
	{
		if (strncmp(data->env[i], key, key_len) == 0 && data->env[i][key_len] == '=')
		{
			free(data->env[i]);
			data->env[i] = new_var;
			return ;
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		perror("malloc");
		free(new_var);
		return ;
	}
	ft_memcpy(new_env, data->env, sizeof(char *) * i);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(data->env);
	data->env = new_env;
}

int	ft_cd(t_command *commands, t_data *data)
{
	char	cwd[PATH_MAX];

	if (!commands || !commands->split_command || count_args(commands->split_command) != 2)
	{
		printf("Usage: cd <directory>\n");
		if (data)
			data->exit_code = 1;
		return (1);
	}
	if (chdir(commands->split_command[1]) != 0)
	{
		perror("cd");
		if (data)
			data->exit_code = 1;
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		update_env(data, "PWD", cwd);
	else
		perror("getcwd");
	if (data)
		data->exit_code = 0;
	return (0);
}
