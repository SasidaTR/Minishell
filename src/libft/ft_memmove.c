#include "../../include/minishell.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!destination || !source)
		return (NULL);
	d = (unsigned char *)destination;
	s = (unsigned char *)source;
	if (d > s)
		while (size--)
			d[size] = s[size];
	else
	{
		i = 0;
		while (i < size)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (destination);
}
