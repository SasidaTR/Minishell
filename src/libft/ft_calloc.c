#include "../../include/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;

	if (count && size && size > 2147483647 / count)
		return (NULL);
	temp = malloc(count * size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, count * size);
	return (temp);
}
