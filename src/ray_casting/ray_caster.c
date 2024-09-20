/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:15:30 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/29 15:28:30 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

static t_vec2	get_vertical_hit(t_cub3d *game, double rad,
					char *hit, double tan_a)
{
	t_vec2	ray_x;
	t_vec2	ret;

	ret = game->player.pos;
	if (rad == 0 || rad == M_PI)
		return (ret.x = __FLT_MAX__, ret);
	ray_x.x = get_offset(game->player.pos, rad, 'v');
	ray_x.y = ray_x.x * tan_a;
	if (ray_x.y < 0)
		ray_x.y *= -1;
	while (42)
	{
		ret_add(&ret, ray_x, rad);
		if (inside_map(game, ret) == false)
			return (ret);
		*hit = hits_wall(game, ret, rad, 'v');
		if (*hit != '0')
			return (ret);
		ray_x.x = (double)REC_WIDTH;
		ray_x.y = ray_x.x * tan_a;
		if (ray_x.y < 0)
			ray_x.y *= -1;
	}
	return (ret);
}

static t_vec2	get_horizontal_hit(t_cub3d *game, double rad,
					char *hit, double tan_a)
{
	t_vec2	ray_y;
	t_vec2	ret;

	ret = game->player.pos;
	if (rad == M_PI_2 || rad == MATH_3PI_2)
		return (ret.y = __FLT_MAX__, ret);
	ray_y.y = get_offset(game->player.pos, rad, 'h');
	ray_y.x = ray_y.y / tan_a;
	if (ray_y.x < 0.0f)
		ray_y.x *= -1;
	while (42)
	{
		ret_add(&ret, ray_y, rad);
		if (inside_map(game, ret) == false)
			return (ret);
		*hit = hits_wall(game, ret, rad, 'h');
		if (*hit != '0')
			return (ret);
		ray_y.y = (double)REC_HEIGHT;
		ray_y.x = ray_y.y / tan_a;
		if (ray_y.x < 0)
			ray_y.x *= -1;
	}
	return (ret);
}

void	ray_caster(t_cub3d *game, t_ray *ray)
{
	t_ray	vert;
	t_ray	hor;
	double	tan_a;

	tan_a = tan(ray->relat_angle);
	hor.pos = get_horizontal_hit(game, ray->relat_angle, &hor.hit, tan_a);
	vert.pos = get_vertical_hit(game, ray->relat_angle, &vert.hit, tan_a);
	hor.dis = distance(game->player.pos, hor.pos);
	vert.dis = distance(game->player.pos, vert.pos);
	if (hor.dis > vert.dis)
	{
		ray->pos = vert.pos;
		ray->dis = vert.dis;
		ray->hit = vert.hit;
		ray->v_h = 'v';
	}
	else
	{
		ray->pos = hor.pos;
		ray->dis = hor.dis;
		ray->hit = hor.hit;
		ray->v_h = 'h';
	}
	ray->dis *= cos(ray->persp_angle);
}
