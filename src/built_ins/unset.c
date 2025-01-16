#include "../../include/minishell.h"

static int check_name_format(char *str)
{
	int i;

	if (!str || !str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (0);

	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void delete_var(char ***env, int index, int *env_size)
{
	int i;

	free((*env)[index]);

	i = index;
	while (i < *env_size - 1)
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	(*env)[*env_size - 1] = NULL;
	(*env_size)--;
}

int ft_unset(t_command *commands, t_data *data)
{
	int i;
	int index;
	if (!commands || !commands->split_command[1])
	{
		printf("unset: not enough arguments");
		return (0);
	}
	i = 1;
	while (commands->split_command[i])
	{
		if (!check_name_format(commands->split_command[i]))
		{
			printf("unset: %s is not a valid identifier\n", commands->split_command[i]);
			data->exit_code = 1;
		}
		else
		{
			index = exist(commands->split_command[i], data->env);
			if (index >= 0)
				delete_var(&data->env, index, &data->env_size);
		}
		i++;
	}
	return (0);
}
