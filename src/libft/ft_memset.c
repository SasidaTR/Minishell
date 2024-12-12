/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:52:53 by earnera           #+#    #+#             */
/*   Updated: 2023/12/06 10:52:53 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ret;

	ret = s;
	while (n--)
	{
		ret[n] = (unsigned char)c;
	}
	return (ret);
}
