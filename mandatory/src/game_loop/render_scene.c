/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:29:49 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/24 15:15:23 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
 *	typedef struct s_image t_image
 *	typedef struct s_color t_color
 *	t_color rgb_to_color(int r, int g, int b)
 *	#define MATH_2PI	6.28318530717958647692528676655900576
 *	#define RAD_AN		0.017453292519943295474371680597869271
 *	#define RAY_COUNT		1920
 *	#define WINDOWS_WIDTH	1920
 *	#define WINDOWS_HEIGHT	1080
 *	#define WALL_SIZE		150
 *	#define REC_HEIGHT	100
 *	#define REC_WIDTH	100
 *	#define NORTH	'N'
 *	#define EAST	'E'
 *	t_color			hex_to_color(unsigned int hex)
 *	t_color			blackout(t_color color, double ratio)
 *	unsigned int	get_pixel_color(t_image img, int x, int y)
 *	void ray_caster(t_cub3d *game, t_ray *ray)
 *	void			put_pixel_to_image(t_image img, int x, int y,
 										unsigned int color)
*/
#include <math.h>
/*
 *	double	fmod(double, double)
 *	double	fmin(double, double)
 *	# define M_PI_2	1.57079632679489661923132169163975144
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

	if (ray.hit == NORTH)
		image = game->images.n;
	else if (ray.hit == SOUTH)
		image = game->images.s;
	else if (ray.hit == EAST)
		image = game->images.e;
	else if (ray.hit == WEST)
		image = game->images.w;
	if (ray.v_h == 'v'
		&& M_PI_2 < ray.relat_angle && ray.relat_angle <= MATH_3PI_2)
		*pix_x = (REC_WIDTH - fmod(ray.pos.y, REC_HEIGHT))
			* image.width / REC_HEIGHT;
	else if (ray.v_h == 'v'
		&& !(M_PI_2 < ray.relat_angle && ray.relat_angle <= MATH_3PI_2))
		*pix_x = fmod(ray.pos.y, REC_HEIGHT) * image.width / REC_HEIGHT;
	else if (ray.v_h == 'h' && (0 < ray.relat_angle && ray.relat_angle <= M_PI))
		*pix_x = (REC_WIDTH - fmod(ray.pos.x, REC_WIDTH))
			* image.width / REC_WIDTH;
	else
		*pix_x = fmod(ray.pos.x, REC_WIDTH) * image.width / REC_WIDTH;
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
