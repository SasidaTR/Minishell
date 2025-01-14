#include "../../include/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*c1 != *c2)
			return ((int)(*c1) - (int)(*c2));
		if (*c1 == '\0')
			return (0);
		c1++;
		c2++;
		n--;
	}
	return (0);
}
