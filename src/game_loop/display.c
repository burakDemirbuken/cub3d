/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:25:51 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
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
// fmod();

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
		image = game->images.E->texture;
		*x = (REC_HEIGHT - fmod(ray.pos.y, REC_HEIGHT))
			* image.width / REC_HEIGHT;
	}
	else if (ray.v_h == 'v')
	{
		image = game->images.W->texture;
		*x = fmod(ray.pos.y, REC_HEIGHT) * image.width / REC_HEIGHT;
	}
	else if (0 < ray.angle && ray.angle <= 180)
	{
		image = game->images.N->texture;
		*x = (REC_WIDTH - fmod(ray.pos.x, REC_WIDTH)) * image.width / REC_WIDTH;
	}
	else
	{
		image = game->images.S->texture;
		*x = (fmod(ray.pos.x, REC_WIDTH)) * image.width / REC_WIDTH;
	}
	return (image);
}

static void	print_walls(t_cub3d *game)
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
			dis = cos(angle_diff) * game->rays[i].dis;
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
	print_floor_ceiling(game);
	print_walls(game);
}
