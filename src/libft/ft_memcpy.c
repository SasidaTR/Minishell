#include "../../include/minishell.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!destination || !source)
		return (NULL);
	d = (unsigned char *)destination;
	s = (unsigned char *)source;
	i = 0;
	while (i < size)
	{
		d[i] = s[i];
		i++;
	}
	return (destination);
}
