/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnera <earnera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:21:35 by earnera           #+#    #+#             */
/*   Updated: 2024/12/03 11:47:44 by earnera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../../include/minishell.h"

void free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
static int	count_characters(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	return (i);
}
int count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			count++;
			while(str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}
char *get_word(char *s, char c)
{	
	int i;
	char *dest;
	int nb_characteres;

	i = 0;
	nb_characteres = count_characters(s,c);
	dest = malloc(sizeof(char) * (nb_characteres + 1));
	while(s[i] && s[i] != c)
	{
		dest [i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char	**ft_split(char *str, char c)
{
	char **tab;
	int nb_words;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb_words = count_words(str,c);
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	while (i < nb_words)
	{	while (str[j] == c)
			j++;
		tab[i] = get_word(&str[j], c);
		if (!tab[i])
		{
			free_split(tab);
			return (NULL);
		}
		j += count_characters(&str[j], c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
