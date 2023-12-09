/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:36:55 by vda-conc          #+#    #+#             */
/*   Updated: 2023/11/16 11:22:03 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_memory(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	return (1);
}

int	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s)
		return (-1);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

size_t	ft_wordlen(char const *s, char c, size_t index)
{
	size_t	i;

	i = 0;
	while (s[index] != c && s[index])
	{
		i++;
		index++;
	}
	return (i);
}

void	ft_fill_element(char *element, const char *src, size_t index,
		size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[index])
		element[i++] = src[index++];
	element[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word_len;
	char	**words;

	words = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!words || ft_count_words(s, c) == -1)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			word_len = ft_wordlen(s, c, i);
			words[j] = malloc((word_len + 1) * sizeof(char));
			if (!words[j] && ft_free_memory(words))
				return (NULL);
			ft_fill_element(words[j++], s, i, word_len);
			i += (word_len - 1);
		}
		i++;
	}
	words[ft_count_words(s, c)] = NULL;
	return (words);
}
