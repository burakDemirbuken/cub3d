/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:26:18 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/05/25 18:40:24 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	lenght;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	lenght = 0;
	while (lenght < len && *(s + start + lenght))
		lenght++;
	a = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!a)
		return (0);
	ft_strlcpy(a, s + start, lenght + 1);
	return (a);
}
