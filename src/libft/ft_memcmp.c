#include "../../include/minishell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	unsigned char	*cs1;
	unsigned char	*cs2;
	size_t			pos;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	pos = 0;
	while (pos < len)
	{
		if (cs1[pos] != cs2[pos])
			return (cs1[pos] - cs2[pos]);
		pos++;
	}
	return (0);
}
