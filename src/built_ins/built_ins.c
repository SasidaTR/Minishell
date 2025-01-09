#include "../../include/minishell.h"

int	ft_echo(char **split_command)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (split_command[i] && ft_strncmp(split_command[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (split_command[i])
	{
		printf("%s", split_command[i]);
		if (split_command[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
int count_args(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return(i);
}

int	ft_cd(char **split_command)
{
	if(!split_command || count_args(split_command) != 2)
	{
		printf("Usage : cd <directory>\n");
		return(1);
	}
	if(chdir(split_command[1]) != 0)
		return(perror("cd"), 0);
	return(0);
	
}

int	ft_pwd(t_data *data)
{
	int i;
	
	i = 0;
	if(!data || !data->env)
	{
		return(printf("Error with env"), 1);
	}
	while(data->env[i])
	{
		if(strncmp(data->env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", &data->env[i][4]);
			return(0);
		}
		i++;
	}
	printf("Error: PWD not found in env");
	return(1);
}

int	ft_export(void)
{
	return (0);
}

int	ft_unset(void)
{
	return (0);
}
