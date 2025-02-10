#include "../../include/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;

	if (count && size && size > 2147483647 / count)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}
