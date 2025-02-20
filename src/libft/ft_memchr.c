/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:43:29 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:43:29 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	unsigned char	*tmp;
	size_t			pos;

	tmp = (unsigned char *)memoryBlock;
	pos = 0;
	while (pos < size)
	{
		if (tmp[pos] == (unsigned char)searchedChar)
			return (&tmp[pos]);
		pos++;
	}
	return (NULL);
}
