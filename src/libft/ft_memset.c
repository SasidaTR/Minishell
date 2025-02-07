#include "../../include/minishell.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*str;

	str = pointer;
	while (count--)
		*str++ = (unsigned char)value;
	return (pointer);
}
