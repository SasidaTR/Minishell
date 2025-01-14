#include "../../include/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ret;

	ret = (unsigned char *)s;
	while (n--)
		ret[n] = (unsigned char)c;
	return (ret);
}
