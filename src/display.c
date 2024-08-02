/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/02 20:42:50 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/*
 *	typedef struct s_image t_image
 *	typedef struct s_color t_color
 *	t_color rgb_to_color(int r, int g, int b)
 *	void put_pixel_to_image(t_image img, int x, int y, unsigned int color)
 *	WINDOWS_WIDTH	1920
 *	WINDOWS_HEIGHT	1080
 *	RAY_COUNT		1920
 *	WALL_SIZE		150
 *	PERSPECTIVE		60.0f
*/
#include <math.h>
/*
 *	double cos(double)
 */

static void	draw_gradyan_vertical(t_image img, int y, t_color color, int width)
{
	double		i;
	double	intensity;
	t_color t_color;

	i = 0;
	while (i <= width / 2)
	{
		t_color = color;
		intensity = i / ((double)width / 2.0) + 0.42;
		if (intensity < 0.0)
			intensity = 0;
		t_color = rgb_to_color(color.r * intensity,
				color.g * intensity, color.b * intensity);
		put_pixel_to_image(img, i, y, t_color.hex);
		put_pixel_to_image(img, width - i, y, t_color.hex);
		i++;
	}
}

static void	draw_floor_ceiling(t_cub3d *game)
{
	int				i;
	t_color			color;
	double			intensity;

	i = 0;
	while (i <= WINDOWS_HEIGHT / 2)
	{
		intensity = i / ((double)WINDOWS_HEIGHT / 2.0) - 0.30;
		if (intensity < 0.0)
			intensity = 0;
		color = rgb_to_color(0 * intensity, 255 * intensity, 0 * intensity);
		draw_gradyan_vertical(game->images.background,
			WINDOWS_HEIGHT / 2 - i, color, WINDOWS_WIDTH);
		color = rgb_to_color(255 * intensity, 0 * intensity, 0 * intensity);
		draw_gradyan_vertical(game->images.background,
			WINDOWS_HEIGHT / 2 + i, color, WINDOWS_WIDTH);
		i++;
	}
}

static void	draw_wall(t_cub3d *game)
{
	double	wall_size;
	int		i;
	double	j;
	int		wall_top;
	double	dis;
	t_color	color;
	//double	intensity;
	t_vec2	image;

	i = 0;
	while (i < RAY_COUNT)
	{
		j = 0;
		double angle_diff = (game->player.angle - game->rays[i].angle) * (M_PI / 180.0);
		dis = cos(angle_diff) * game->rays[i].dis;
		wall_size = (WINDOWS_HEIGHT / dis);
		if (wall_size > 10)
			wall_size = 10;
		wall_size *= WALL_SIZE;
		wall_top = (WINDOWS_HEIGHT - wall_size) / 2;

		image.x = (fmod(game->rays[i].pos.x, REC_WIDTH));

		while (j < wall_size)
		{
			color = hex_to_color(*(unsigned int*)(game->images.mahmut.data + (int)((j) * game->images.mahmut.line_lenght + image.x * (game->images.mahmut.bits_per_pixel / 8))));
			put_pixel_to_image(game->images.background, i, wall_top + j, color.hex);
			j += 1;
		}

/* 		intensity = 1.0 - (game->rays	[i].dis / 410);
		if (intensity < 0.0)
			intensity = 0.0;
		if (intensity > 1.0)
			intensity = 1.0;
		if (game->rays[i].v_h == 'v')
			color = rgb_to_color(0x00 * intensity, 0x00 * intensity, 124 * intensity);
		else
			color = rgb_to_color(0x00 * intensity, 124 * intensity, 0x00 * intensity);
		draw_rectangle(game->images.background, i * (WINDOWS_WIDTH / RAY_COUNT),
			wall_top, (WINDOWS_WIDTH / RAY_COUNT), (int)wall_size, false, color.hex); */
		i++;
	}
}

void	display(t_cub3d *game)
{
	draw_floor_ceiling(game);
	draw_wall(game);
}
