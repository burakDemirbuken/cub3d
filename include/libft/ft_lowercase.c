/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowercase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:06:35 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/06/23 14:57:20 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 *	size_t	ft_strlen(const char *s)
 *	int		ft_tolower(int c)
 */

char	*ft_lowercase(char *str)
{
	int	i;
	int	str_len;

	i = 0;
	if (!str || !(*str))
		return (0);
	str_len = ft_strlen(str);
	while (i < str_len)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
