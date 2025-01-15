#include "../../include/minishell.h"

void ft_swap_array(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_array(char **array, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (strncmp(array[i], array[j], INT_MAX) > 0)
				ft_swap_array(&array[i], &array[j]);
			j++;
		}
		i++;
	}
}
