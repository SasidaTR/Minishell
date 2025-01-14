#include "../../include/minishell.h"
#include <limits.h>

int count_args(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return(i);
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

	// Mise à jour du PWD dans la variable d'environnement
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
		data->exit_code = 0; // Indiquer le succès
	return (0);
}