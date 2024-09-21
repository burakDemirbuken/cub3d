/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/21 11:48:24 by bdemirbu         ###   ########.fr       */
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
/*
 *	double fmod(double, double)
 */

static unsigned int	darken_pix_color(t_image image, double x, double y,
						double shadow)
{
	t_color	color;

	color = hex_to_color(get_pixel_color(image, x, y));
	color = blackout(color, shadow);
	return (color.hex);
}

static void	print_slice(t_cub3d *game, t_image img, int x, double pix_x)
{
	int		i;
	double	ratio;
	double	shadow;
	double	slice_size;
	double	slice_top;

	slice_size = (WINDOWS_HEIGHT / game->rays[x].dis) * WALL_SIZE;
	slice_size = fmin(slice_size, 15000);
	slice_top = (WINDOWS_HEIGHT - slice_size) / 2;
	ratio = img.height / slice_size;
	shadow = game->rays[x].dis / 420;
	i = -1;
	while (++i < slice_size)
	{
		if (WINDOWS_HEIGHT > slice_top + i && slice_top + i >= 0
			&& WINDOWS_WIDTH > x && x >= 0)
		{
			if (game->shadow)
				put_pixel_to_image(game->images.background, x, slice_top + i,
					darken_pix_color(img, pix_x, i * ratio, shadow));
			else
				put_pixel_to_image(game->images.background, x, slice_top + i,
					get_pixel_color(img, pix_x, i * ratio));
		}
	}
}

static t_image	which_image(t_cub3d *game, double *pix_x, t_ray ray)
{
	t_image	image;

	if (ray.v_h == 'v')
	{
		if (ray.hit == DOOR)
			image = game->images.door;
		else if (ray.hit == EAST)
			image = game->images.e->texture;
		else
			image = game->images.w->texture;
		*pix_x = fmod(ray.pos.y, REC_HEIGHT) * image.width / REC_HEIGHT;
	}
	else
	{
		if (ray.hit == DOOR)
			image = game->images.door;
		else if (ray.hit == NORTH)
			image = game->images.n->texture;
		else
			image = game->images.s->texture;
		*pix_x = fmod(ray.pos.x, REC_WIDTH) * image.width / REC_WIDTH;
	}
	return (image);
}

static void	set_relative_ray_angle(t_ray *ray, double player_angle)
{
	ray->relat_angle = ray->persp_angle + player_angle;
	if (ray->relat_angle < 0)
		ray->relat_angle += MATH_2PI;
	if (ray->relat_angle >= MATH_2PI)
		ray->relat_angle -= MATH_2PI;
	if (fmod(ray->relat_angle, M_PI_2 / 2) == 0)
		ray->relat_angle += RAD_ANG * 0.00042;
}

void	render_scene(t_cub3d *game)
{
	int		i;
	double	pix_x;
	t_image	image;

	i = 0;
	while (i < RAY_COUNT)
	{
		set_relative_ray_angle(&game->rays[i], game->player.angle);
		ray_caster(game, &game->rays[i]);
		image = which_image(game, &pix_x, game->rays[i]);
		print_slice(game, image, i, pix_x);
		i++;
	}
}
