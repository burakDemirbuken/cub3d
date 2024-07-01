/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:44:58 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/05/12 14:44:47 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_digitcount(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*a;
	long	num;

	num = (long)n;
	len = ft_digitcount(num);
	if (n == 0)
		return (ft_strdup("0"));
	a = (char *)malloc(sizeof(char) * (len + 1));
	if (!a)
		return (0);
	a[len] = 0;
	if (n < 0)
		num = -num;
	while (len--)
	{
		a[len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		a[0] = '-';
	return (a);
}
