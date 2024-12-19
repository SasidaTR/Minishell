#include "../../include/minishell.h"

int ft_echo(char **splited_command)
{
	int i;
	int newline = 1;

	i = 1;
	if (splited_command[i] && ft_strncmp(splited_command[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (splited_command[i])
	{
		printf("%s", splited_command[i]);
		if(splited_command[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int ft_cd(void)
{
	return (0);
}

int ft_pwd(void)
{
	return (0);
}

int ft_export(void)
{
	return (0);
}

int ft_unset(void)
{
	return (0);
}
