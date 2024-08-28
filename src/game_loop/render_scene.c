/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/28 18:27:34 by bkorkut          ###   ########.fr       */
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
*/
#include <math.h>
// fmod();

//	isim değişecek
static void inline	print_wall(t_cub3d *game, t_image image, double wall_size, /* -> */int a/* <- isim değişecek */, double x, double wall_top)
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

	if (ray.v_h == 'v' && M_PI_2 < ray.relat_angle && ray.relat_angle <= MATH_3PI_2)
	{
		image = game->images.e->texture;
		*x = (REC_HEIGHT - fmod(ray.pos.y, REC_HEIGHT))
			* image.width / REC_HEIGHT;
	}
	else if (ray.v_h == 'v')
	{
		image = game->images.w->texture;
		*x = fmod(ray.pos.y, REC_HEIGHT) * image.width / REC_HEIGHT;
	}
	else if (0 < ray.relat_angle && ray.relat_angle <= M_PI)
	{
		image = game->images.n->texture;
		*x = (REC_WIDTH - fmod(ray.pos.x, REC_WIDTH)) * image.width / REC_WIDTH;
	}
	else
	{
		image = game->images.s->texture;
		*x = fmod(ray.pos.x, REC_WIDTH) * image.width / REC_WIDTH;
	}
	return (image);
}

static void	set_relative_ray_angle(t_ray *ray, double player_angle)
{
	ray->relat_angle = ray->persp_angle + player_angle;
	if (ray->relat_angle < 0)
		ray->relat_angle += MATH_2PI;
	if (ray->relat_angle > MATH_2PI)
		ray->relat_angle -= MATH_2PI;
	if (fmod(ray->relat_angle, M_PI_2 / 2) == 0)
		ray->relat_angle += RAD_ANG * 0.000042;
}

// get wall / door distance
// scale said slice
// determine which image to use
// paint slice

void	render_scene(t_cub3d *game)
{
	// "wich image" stays the same if the ray hits the same wall.. optimize?
	double	wall_size;
	int		i;
	int		wall_top;
	double	x;
	double	a;
	t_image	image;

	i = 0;
	a = 0;
	while (i < RAY_COUNT)
	{
		set_relative_ray_angle(&game->rays[i], game->player.angle);
		cast_ray(game, &game->rays[i]);
		// scale_texture_slice();
		// paint_texture_slice();
		wall_size = (WINDOWS_HEIGHT / game->rays[i].dis);
		if (wall_size > 100)
			wall_size = 100;
		wall_size *= WALL_SIZE;
		wall_top = (WINDOWS_HEIGHT - wall_size) / 2;
		image = which_image(game, &x, game->rays[i]);
		print_wall(game, image, wall_size, i, x, wall_top);
		i++;
	}
}