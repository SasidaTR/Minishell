#include "../../include/minishell.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	x;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		x = -n;
	}
	else
		x = n;
	if (x >= 10)
		ft_putnbr_fd(x / 10, fd);
	c = x % 10 + '0';
	write(fd, &c, 1);
}
