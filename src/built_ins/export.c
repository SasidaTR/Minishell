#include "../../include/minishell.h"

static int check_format(char *str)
{
	int i;

	if (!str || !str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}

	if (str[i] == '=' && !str[i + 1])
		return (1);

	return (1);
}

int exist(char *str, char **env)
{
	int i;
	int var_len;

	i = 0;
	var_len = 0;
	while (str[var_len] && str[var_len] != '=')
		var_len++;
	while (env[i])
	{
		if (strncmp(env[i], str, var_len) == 0 && (env[i][var_len] == '\0' || env[i][var_len] == '='))
			return (i);
		i++;
	}
	return (-1);
}
static bool add_or_replace_env(char *str, char ***env, t_data *data)
{
    int pos;
    char *new_var;
    char **temp;

    pos = exist(str, *env);
    new_var = ft_strdup(str);
    if (!new_var)
        return false;

    if (pos >= 0 && ft_strchr(str, '='))
    {
        free((*env)[pos]);
        (*env)[pos] = new_var;
    }
    else
    {
        temp = ft_realloc(*env, data->env_size * sizeof(char *), (data->env_size + 2) * sizeof(char *));
        if (!temp)
        {
            free(new_var);
            return false;
        }
        *env = temp;
        (*env)[data->env_size] = new_var;
        (*env)[data->env_size + 1] = NULL;
        data->env_size++;
    }

    return true;
}

void print_sorted_env(int size, char **env)
{
    char **sorted_env;
    char *value;
    int i;
    int j;

    sorted_env = malloc(sizeof(char *) * (size + 1));
    if (!sorted_env)
        return;
    i = 0;
    while (i < size)
    {
        sorted_env[i] = ft_strdup(env[i]);
        i++;
    }
    sorted_env[size] = NULL;
    sort_array(sorted_env, size);
    i = 0;
    while (sorted_env[i])
    {
        printf("declare -x ");
        j = 0;
        while (sorted_env[i][j] && sorted_env[i][j] != '=')
        {
            ft_putchar(sorted_env[i][j]);
            j++;
        }
        value = ft_strchr(sorted_env[i], '=');
        if (value)
            printf("=\"%s\"\n", value + 1);
        else
            printf("\n");
        i++;
    }
    i = 0;
    while (i < size)
    {
        free(sorted_env[i]);
        i++;
    }
    free(sorted_env);
}

int ft_export(t_command *commands, t_data *data)
{
	int i;

	i = 1;
	if (!commands || !commands->split_command[1])
		return (print_sorted_env(data->env_size, data->env), 0);
	while (commands->split_command[i])
	{
		if (!check_format(commands->split_command[i]))
		{
			printf("export: %s is not a valid identifier\n", 
				commands->split_command[i]);
			data->exit_code = 1;
		}
		else if (!add_or_replace_env(commands->split_command[i], 
				&data->env, data))
			return (printf("export: memory allocation error\n"), 1);
		i++;
	}
	return (data->exit_code);
}