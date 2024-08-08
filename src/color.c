/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:26:42 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/01 14:54:02 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/*
 *	typedef struct s_color t_color
 */

t_color	rgb_to_color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.hex = (r << 16) | (g << 8) | b;
	return (color);
}

t_color	hex_to_color(unsigned int hex)
{
	t_color	color;

	color.r = (hex & 0xFF0000) >> 16;
	color.g = (hex & 0xFF00) >> 8;
	color.b = hex & 0xFF;
	color.hex = hex;
	return (color);
}
