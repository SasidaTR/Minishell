#include "../../include/minishell.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;
	long	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = (nb * 10) + str[i] - '0';
		i++;
	}
	return (nb * neg);
}