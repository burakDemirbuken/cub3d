/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/07 08:23:28 by bdemirbu         ###   ########.fr       */
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

static void inline	draw_gradyan_vertical(t_cub3d *game, t_image img, int y, t_color color, int width)
{
	double		i;
	t_color t_color;

	i = 0;
	while (i <= width / 2)
	{
		t_color = color;
		if (game->shadow)
			t_color = blackout(t_color, 1.0 - (i / ((double)width / 2.0) + 0.42));
		put_pixel_to_image(img, i, y, t_color.hex);
		put_pixel_to_image(img, width - i, y, t_color.hex);
		i++;
	}
}

static void inline	draw_floor_ceiling(t_cub3d *game)
{
	int				i;
	t_color			color;

	i = 0;
	while (i <= WINDOWS_HEIGHT / 2)
	{
		color = rgb_to_color(0 , 0, 255);
		if (game->shadow)
			color = blackout(color, 1.0 - (i / (((double)WINDOWS_HEIGHT / 2.0))) + 0.32);
		draw_gradyan_vertical(game, game->images.background,
			WINDOWS_HEIGHT / 2 - i, color, WINDOWS_WIDTH);
		color = rgb_to_color(123, 0, 255);
		if (game->shadow)
			color = blackout(color, 1.0 - (i / ((double)WINDOWS_HEIGHT / 2.0)) + 0.32);
		draw_gradyan_vertical(game, game->images.background,
			WINDOWS_HEIGHT / 2 + i, color, WINDOWS_WIDTH);
		i++;
	}
}

//	isim değişecek
static void inline	wall(t_cub3d *game, t_image image, double wall_size, /* -> */int a/* <- isim değişecek */, double x, double wall_top)
{
	int		i;
	t_color	color;
	double	ratio;
	double	ratio_color;

	i = 0;
	ratio = image.height / wall_size;
	ratio_color = game->rays[a].dis / 420;
	while (i < wall_size)
	{
		if (WINDOWS_HEIGHT > wall_top + i && wall_top + i >= 0 && WINDOWS_WIDTH > a && a >= 0)
		{
			if (game->shadow)
			{
				color = hex_to_color(get_pixel_color(image, x, i * ratio));
				color = blackout(color, ratio_color);
				put_pixel_to_image(game->images.background, a, wall_top + i, color.hex);
			}
			else
				put_pixel_to_image(game->images.background, a, wall_top + i,
					get_pixel_color(image, x, i * ratio));
		}
		i++;
	}
}

static inline t_image	which_image(t_cub3d *game, double *x, t_ray ray)
{
	t_image	image;

	if (ray.v_h == 'v' && 90 < ray.angle && ray.angle <= 270)
	{
		image = game->images.E;
		*x = (REC_HEIGHT - fmod(ray.pos.y, REC_HEIGHT))
			* image.width / REC_HEIGHT;
	}
	else if (ray.v_h == 'v')
	{
		image = game->images.W;
		*x = fmod(ray.pos.y, REC_HEIGHT) * image.width / REC_HEIGHT;
	}
	else if (0 < ray.angle && ray.angle <= 180)
	{
		image = game->images.N;
		*x = (REC_WIDTH - fmod(ray.pos.x, REC_WIDTH)) * image.width / REC_WIDTH;
	}
	else
	{
		image = game->images.S;
		*x = (fmod(ray.pos.x, REC_WIDTH)) * image.width / REC_WIDTH;
	}
	return (image);
}

static void	draw_wall(t_cub3d *game)
{
	double	wall_size;
	int		i;
	int		wall_top;
	double	dis;
	double	x;
	double	a;
	t_image	image;
	double	angle_diff;

	i = 0;
	a = 0;
	while (i < RAY_COUNT)
	{
		game->rays[i] =  ray_throw(game, game->player.angle + a - (PERSPECTIVE / 2.0));
		a += PERSPECTIVE / RAY_COUNT;
		angle_diff = (game->player.angle - game->rays[i].angle) * RAD_CONVERT;
		if (game->rays[i].dis > 100)
			dis = cos(angle_diff) * game->rays[i].dis;
		else
			dis = game->rays[i].dis;
		wall_size = (WINDOWS_HEIGHT / dis);
		if (wall_size > 100)
			wall_size = 100;
		wall_size *= WALL_SIZE;
		wall_top = (WINDOWS_HEIGHT - wall_size) / 2;
		image = which_image(game, &x, game->rays[i]);
		wall(game, image, wall_size, i, x, wall_top);
		i++;
	}
}
//isim değişikliği olucka
void	display(t_cub3d *game)
{
	draw_floor_ceiling(game);
	draw_wall(game);
}
