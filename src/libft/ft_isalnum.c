#include "../../include/minishell.h"

int ft_isalnum(int c)
{
    if ((c <= '9' && c >= '0') || (c <= 'z' && c >= 'a') 
            || (c <= 'Z' && c >= 'A'))
        return (1);
    else
        return (0);
}