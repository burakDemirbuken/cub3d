/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:10:55 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/26 12:55:53 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft/libft.h"

static unsigned int	rgb_to_hex(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

static void	skip_to_colour(char **str)
{
	while (**str >= '0' && **str <= '9')
		(*str)++;
	while (!(**str >= '0' && **str <= '9'))
		(*str)++;
}

unsigned int get_colour(char *str)
{
	int	red;
	int	green;
	int	blue;

	skip_to_colour(&str);
	red = ft_atoi(str);
	skip_to_colour(&str);
	green = ft_atoi(str);
	skip_to_colour(&str);
	blue = ft_atoi(str);
	// if (red / 256 != 0 | green / 256 != 0 | blue / 256 != 0)
	// 	; // NEEDS A BIG FAT ERROR CHECK!
	return (rgb_to_hex(red, green, blue));
}
