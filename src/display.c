/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/27 14:30:06 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

void display(t_cub3d *game)
{
	double			wall_size;
	int				i;
	int				wall_top;
	double			dis;
	unsigned int	color;
	double			intensity;

	i = 0;
/* 	while (i < RAY_COUNT)
	{
		double temp = (game->player.angle - game->rays[i].angle) * (M_PI / 180.0);
		dis = cos(temp) * game->rays[i].dis;
		intensity = 1.0 - (dis / 700);
		if (intensity < 0.0)
			intensity = 0.0;
		if (intensity > 1.0)
			intensity = 1.0;

		unsigned int r, g, b;
			r = (unsigned int)(15 * intensity);
			g = (unsigned int)(210 * intensity);
			b = (unsigned int)(210 * intensity);
		color = (r << 16) | (g << 8) | b;
		draw_rectangle(game->images.background,WINDOWS_WIDTH + i, 0, 1, WINDOWS_HEIGHT / 2, false, color);
			r = (unsigned int)(210 * intensity);
			g = (unsigned int)(15 * intensity);
			b = (unsigned int)(67 * intensity);
		color = (r << 16) | (g << 8) | b;
		draw_rectangle(game->images.background,WINDOWS_WIDTH + i, WINDOWS_HEIGHT / 2, 1, WINDOWS_HEIGHT / 2, false, color);
		i++;
	} */
	draw_rectangle(game->images.background, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT / 2, false, 0x39487362);
	draw_rectangle(game->images.background, 0, WINDOWS_HEIGHT / 2 , WINDOWS_WIDTH, WINDOWS_HEIGHT / 2, false, 0x34523234);
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
		intensity = 1.0 - (dis / 700);
		if (intensity < 0.0)
			intensity = 0.0;
		if (intensity > 1.0)
			intensity = 1.0;
 		unsigned int r, g, b;
		if (game->rays[i].v_h == 'v')
		{
			r = (unsigned int)(0x29 * intensity);
			g = (unsigned int)(0x68 * intensity);
			b = (unsigned int)(0x00 * intensity);
		}
		else
		{
			r = (unsigned int)(0x00 * intensity);
			g = (unsigned int)(0x45 * intensity);
			b = (unsigned int)(0x31 * intensity);
		}

		color = (r << 16) | (g << 8) | b;
		draw_rectangle(game->images.background, i * (WINDOWS_WIDTH / RAY_COUNT),
			wall_top, (WINDOWS_WIDTH / RAY_COUNT), (int)wall_size, false, color);
		i++;
	}
}
