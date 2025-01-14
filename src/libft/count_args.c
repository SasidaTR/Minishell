#include "../../include/minishell.h"

int count_args(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return(i);
}