/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:44:27 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/06/26 11:06:52 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	if (count <= 0 || size <= 0)
		return (0);
	a = (void *)malloc(count * size);
	if (!a)
		return (0);
	return (ft_memset(a, 0, count * size));
}
