#include "../../include/minishell.h"

static void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static int	count_characters(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_words(char *str, char c)
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
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*get_word(char *s, char c)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (count_characters(s, c) + 1));
	if (!dest)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char *str, char c)
{
	char	**tab;
	int		nb_words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nb_words = count_words(str, c);
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	while (i < nb_words)
	{
		while (str[j] == c)
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
