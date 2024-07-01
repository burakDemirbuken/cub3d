/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:20:13 by bdemirbu          #+#    #+#             */
/*   Updated: 2023/10/14 15:29:59 by bdemirbu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	lenght;

	lenght = ft_strlen(s1);
	dup = (char *)malloc(lenght + 1);
	if (!dup)
		return (0);
	ft_strlcpy(dup, s1, lenght + 1);
	return (dup);
}
