#include "../../include/minishell.h"

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