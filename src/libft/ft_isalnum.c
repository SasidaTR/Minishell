#include "../../include/minishell.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha((unsigned char)c) || ft_isdigit((unsigned char)c));
}
