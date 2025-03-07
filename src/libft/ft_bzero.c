/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:42:55 by earnera           #+#    #+#             */
/*   Updated: 2025/02/20 12:42:55 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n--)
		*str++ = 0;
	return (s);
}
