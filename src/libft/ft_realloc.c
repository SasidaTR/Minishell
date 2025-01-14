#include "../../include/minishell.h"


void	*ft_realloc(void *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	cur_size;

	if (ptr == NULL)
		return (malloc(new_size));
	cur_size = sizeof(ptr);
	if (new_size <= cur_size)
		return (ptr);
	new_ptr = malloc(new_size);
    if(new_ptr == NULL)
    {
        return (NULL);
    }
	ft_memcpy(ptr, new_ptr, cur_size);
	free(ptr);
	return (new_ptr);
}