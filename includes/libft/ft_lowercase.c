/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowercase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:06:35 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:15:53 by bkorkut          ###   ########.fr       */
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
