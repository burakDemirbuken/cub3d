/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:17:27 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/20 15:42:47 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// typedef t_color

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

t_color	blackout(t_color color, double ratio)
{
	double	intensity;

	intensity = 1.0 - ratio;
	if (intensity < 0.0)
		intensity = 0.0;
	if (intensity > 1.0)
		intensity = 1.0;
	return (rgb_to_color(color.r * intensity,
			color.g * intensity, color.b * intensity));
}
