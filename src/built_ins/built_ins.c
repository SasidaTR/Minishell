#include "../../include/minishell.h"

// pas finie, il reste à gérer les \n et les quotes (faudrait un parsing fonctionnel pr ça certainement)
int ft_echo(char **args)
{
	int i;
	int newline = 1;

	i = 1;
	if(args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while(args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if(newline)
		printf("\n");
	return(0);
}

int ft_cd(void)
{
	return(0);
}

int ft_pwd(void)
{
	return(0);
}

int ft_export(void)
{
	return(0);
}

int ft_unset(void)
{
	return(0);
}
