#include "../../include/minishell.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	while (*string)
	{
		if (*string == (unsigned char)searchedChar)
			return ((char *)string);
		string++;
	}
	if (*string == (unsigned char)searchedChar)
		return ((char *)string);
	return (NULL);
}
