/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:41:28 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/05 14:58:49 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/*
 *	typedef struct s_image t_image
 */

void	put_pixel_to_image(t_image img, int x, int y, unsigned int color)
{
	if (img.height > y && y >= 0 && img.width > x && x >= 0)
		*(unsigned int*)(img.data + (int)(y * img.line_lenght +
			x * (img.bits_per_pixel / 8))) = color;
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
