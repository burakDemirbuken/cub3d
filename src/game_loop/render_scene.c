/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/17 20:20:07 by bdemirbu         ###   ########.fr       */
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

static void	print_wall(t_cub3d *game, t_image image, double wall_size, int ray_index, double x, double wall_top)
{
	int		i;
	t_color	color;
	double	ratio;
	double	ratio_color;

	i = -1;
	ratio = image.height / wall_size;
	ratio_color = game->rays[ray_index].dis / 420;
	while (++i < wall_size)
	{
		if (WINDOWS_HEIGHT > wall_top + i && wall_top + i >= 0
			&& WINDOWS_WIDTH > ray_index && ray_index >= 0)
		{
			if (game->shadow)
			{
				color = hex_to_color(get_pixel_color(image, x, i * ratio));
				color = blackout(color, ratio_color);
				put_pixel_to_image(game->images.background, ray_index,
					wall_top + i, color.hex);
			}
			else
				put_pixel_to_image(game->images.background, ray_index,
					wall_top + i, get_pixel_color(image, x, i * ratio));
		}
	}
}

static t_image	which_image(t_cub3d *game, double *x, t_ray ray)
{
	t_image	image;

	if (ray.v_h == 'v')
	{
		if (ray.hit == '2')
			image = game->images.door->texture;
		else if (ray.hit == 'E')
			image = game->images.e->texture;
		else
			image = game->images.w->texture;
		*x = fmod(ray.pos.y, REC_HEIGHT) * image.width / REC_HEIGHT;
	}
	else
	{
		if (ray.hit == '2')
			image = game->images.door->texture;
		else if (ray.hit == 'N')
			image = game->images.n->texture;
		else
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

void	render_scene(t_cub3d *game)
{
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
		ray_caster(game, &game->rays[i]);
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
