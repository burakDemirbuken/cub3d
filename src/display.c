/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/30 17:27:09 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

void	put_pixel_to_image(t_image img, int x, int y, int color)
{
	if (img.height > y && y >= 0 && (img.width > x && x >= 0))
		*(unsigned int*)(img.data + (int)(y * img.line_lenght +
			x * (img.bits_per_pixel / 8))) = color;
}

void	draw_gradyan_vertical(t_image img, int y, int color, int width)
{
	double		i;
	double	intensity;
	unsigned int t_color;

	i = 0;
	while (i <= width / 2)
	{
		t_color = color;
		intensity = i / ((double)width / 2.0) + 0.42;
		if (intensity < 0.0)
			intensity = 0;
		unsigned int r, g, b;
			r = ((color & 0x00FF0000) >> 16) * intensity;
			g = ((color & 0x0000FF00) >> 8) * intensity;
			b = (color & 0x000000FF) * intensity;
		t_color = (r << 16) | (g << 8) | b;
		put_pixel_to_image(img, i, y, t_color);
		put_pixel_to_image(img, width - i, y, t_color);
		i++;
	}
}

void	display(t_cub3d *game)
{
	double			wall_size;
	int				i;
	int				wall_top;
	double			dis;
	unsigned int	color;
	double			intensity;

	i = 0;
	while (i < WINDOWS_HEIGHT / 2)
	{
		intensity = i / ((double)WINDOWS_HEIGHT / 2.0) - 0.30;
		if (intensity < 0.0)
			intensity = 0;
		unsigned int r, g, b;
			r = (unsigned int)(0 * intensity);
			g = (unsigned int)(125 * intensity);
			b = (unsigned int)(0 * intensity);
		color = (r << 16) | (g << 8) | b;
		//draw_gradyan_vertical(game->images.background, i, 0, color, 100);
		draw_gradyan_vertical(game->images.background, WINDOWS_HEIGHT / 2 - i, color, WINDOWS_WIDTH);
		//draw_rectangle(game->images.background, 0, WINDOWS_HEIGHT / 2 - i, WINDOWS_WIDTH, 1, false, color);

			r = (unsigned int)(0 * intensity);
			g = (unsigned int)(125 * intensity);
			b = (unsigned int)(0 * intensity);
		color = (r << 16) | (g << 8) | b;
		draw_gradyan_vertical(game->images.background, WINDOWS_HEIGHT / 2 + i, color, WINDOWS_WIDTH);
		i++;
	}
	i = 0;
	color = 0;
	while (i < RAY_COUNT)
	{
		double angle_diff = (game->player.angle - game->rays[i].angle) * (M_PI / 180.0);
		dis = cos(angle_diff) * game->rays[i].dis;
		wall_size = (WINDOWS_HEIGHT / dis);
		if (wall_size > 10)
			wall_size = 10;
		wall_size *= WALL_SIZE;
		wall_top = (WINDOWS_HEIGHT - wall_size) / 2;
		intensity = 1.0 - (game->rays[i].dis / 410);
		if (intensity < 0.0)
			intensity = 0.0;
		if (intensity > 1.0)
			intensity = 1.0;
 		unsigned int r, g, b;
		if (game->rays[i].v_h == 'v')
		{
			r = (unsigned int)(124 * intensity);
			g = (unsigned int)(0x00 * intensity);
			b = (unsigned int)(0x00 * intensity);
		}
		else
		{
			r = (unsigned int)(0x00 * intensity);
			g = (unsigned int)(124 * intensity);
			b = (unsigned int)(0x00 * intensity);
		}

		color = (r << 16) | (g << 8) | b;
		draw_rectangle(game->images.background, i * (WINDOWS_WIDTH / RAY_COUNT),
			wall_top, (WINDOWS_WIDTH / RAY_COUNT), (int)wall_size, false, color);
		i++;
	}
}
