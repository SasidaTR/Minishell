#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\r'
		|| c == '\f' || c == '\t' || c == '\v');
}
