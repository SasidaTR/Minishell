#include "../../include/minishell.h"


void update_env(t_data *data, const char *key, const char *value) 
{
    int i = 0;
    size_t key_len = strlen(key);
    size_t value_len = strlen(value);
    char *new_var = malloc(key_len + value_len + 2);
	char **new_env;
    if (!new_var) 
	{
        perror("malloc");
        return;
    }
    ft_memcpy(new_var, key, key_len);
    new_var[key_len] = '=';
    ft_memcpy(new_var + key_len + 1, value, value_len);
    new_var[key_len + value_len + 1] = '\0';
    while (data->env && data->env[i]) 
	{
        if (strncmp(data->env[i], key, key_len) == 0 && data->env[i][key_len] == '=') 
		{
            free(data->env[i]);
            data->env[i] = new_var;
            return;
        }
        i++;
    }
    new_env = ft_realloc(data->env, sizeof(char *) * (i + 2));
    if (!new_env) 
	{
        perror("realloc");
        free(new_var);
        return;
    }
    new_env[i] = new_var;
    new_env[i + 1] = NULL;
    data->env = new_env;
}



int	ft_cd(t_command *commands, t_data *data)
{
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

	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)))
	{
		update_env(data, "PWD", cwd);
	}
	else
	{
		perror("getcwd");
	}

	if (data)
		data->exit_code = 0;
	return (0);
}