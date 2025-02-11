#include "../../include/minishell.h"

static bool	export_no_args(t_list *env)
{
	char	**arr;
	int		i;
	int		j;

	arr = lst_to_arr(env);
	if (!arr)
		return (false);
	sort_array(arr, len_list(env));
	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free(arr);
	return (true);
}

static bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	exist(char *str, t_list *env)
{
	int		i;
	int		j;
	t_list	*temp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	temp = env;
	if (!ft_strncmp(temp->str, str, i) && (temp->str[i] == '\0' || \
		temp->str[i] == '='))
		return (j);
	temp = temp->next;
	j++;
	while (temp != env)
	{
		if (!ft_strncmp(temp->str, str, i) && (temp->str[i] == '\0' || \
			temp->str[i] == '='))
			return (j);
		temp = temp->next;
		j++;
	}
	return (-1);
}

bool	export(char *str, t_list **env)
{
	int		pos;
	int		i;
	char	*value;

	pos = exist(str, (*env));
	value = ft_strdup(str);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		i = 0;
		while (i < pos)
		{
			(*env) = (*env)->next;
			i++;
		}
		free((*env)->str);
		(*env)->str = value;
	}
	else if (pos == -1)
		if (!append(env, value))
			return (false);
	return (true);
}

int	ft_export(char **str, t_list **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (*env && !export_no_args((*env)))
			return (print_error(ERR_MALLOC));
		return (0);
	}
	while (str[i])
	{
		if (!valid_identifier(str[i]))
		{
			print_error("export: not a valid identifier\n");
			exit_code = 1;
		}
		else if (!export(str[i], env))
			return (print_error(ERR_MALLOC));
		i++;
	}
	return (exit_code);
}
