#include "../../include/minishell.h"

static char	*get_env_var(const char *name, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*replace_variable(const char *str, char **env)
{
	char	*start;
	char	*end;
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*result;
	char	*final_result;

	start = ft_strchr(str, '$');
	if (!start || !ft_isalpha(start[1]))
		return (ft_strdup(str));
	end = start + 1;
	while (ft_isalnum(*end) || *end == '_')
		end++;
	var_name = ft_substr(start + 1, 0, end - start - 1);
	var_value = get_env_var(var_name, env);
	free(var_name);
	if (!var_value)
		return (ft_strdup(str));
	prefix = ft_substr(str, 0, start - str);
	result = ft_strjoin(prefix, var_value);
	free(prefix);
	final_result = ft_strjoin(result, end);
	free(result);
	return (final_result);
}

void	expand_variables(t_command *commands, char **env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (commands->pipeline[i])
	{
		expanded = replace_variable(commands->pipeline[i], env);
		free(commands->pipeline[i]);
		commands->pipeline[i] = expanded;
		i++;
	}
}
