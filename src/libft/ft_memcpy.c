/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:43:35 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:43:35 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!destination || !source)
		return (NULL);
	d = (unsigned char *)destination;
	s = (unsigned char *)source;
	i = 0;
	while (i < size)
	{
		d[i] = s[i];
		i++;
	}
	return (destination);
}
