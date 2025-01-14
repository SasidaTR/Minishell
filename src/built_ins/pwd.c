#include "../../include/minishell.h"

int	ft_pwd(t_data *data)
{
	int	i;
	
	i = 0;
	if (!data || !data->env)
		return (printf("Error with env"), 1);
	while (data->env[i])
	{
		if (strncmp(data->env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", &data->env[i][4]);
			return (0);
		}
		i++;
	}
	printf("Error: PWD not found in env");
	return (1);
}
