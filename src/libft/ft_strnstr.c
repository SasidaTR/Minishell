/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:44:36 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:44:36 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_search(char *big, int index, char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (big[i + index] == little[i] && big[i + index] && (i + index) < len)
		i++;
	if (little[i])
		return (0);
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len && (unsigned char)big[i])
	{
		if (ft_search((char *)big, i, (char *)little, len))
			return ((char *)big + i);
		i++;
	}
	return (0);
}
