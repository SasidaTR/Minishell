/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:43:41 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:43:41 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*str;

	str = pointer;
	while (count--)
		*str++ = (unsigned char)value;
	return (pointer);
}
