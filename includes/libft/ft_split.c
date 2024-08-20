/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:49:25 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:16:57 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		count++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (count);
}

void	ft_strfree(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

static	size_t	ft_wordlen(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (*str != c && *str)
	{
		len++;
		str++;
	}
	return (len);
}

char	**ft_split(const char *s, char c)
{
	char	**a;
	size_t	word_count;
	size_t	i;
	size_t	length;

	word_count = ft_wordcount(s, c);
	a = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!a)
		return (0);
	i = 0;
	while (i < word_count)
	{
		while (*s && *s == c)
			s++;
		length = ft_wordlen(s, c);
		a[i] = ft_substr(s, 0, length);
		if (!a[i])
			return (ft_strfree(a), NULL);
		s += length;
		i++;
	}
	a[i] = 0;
	return (a);
}
