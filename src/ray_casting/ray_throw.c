/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_throw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:31:32 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/26 18:18:19 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// typedef t_cub3d;
// typedef t_ray;
// typedef t_vec2;
#include <math.h>
// tan();

// t_ray	ray_throw(t_cub3d *game, double angle)
void	ray_throw(t_cub3d *game, t_ray *ray)
{
	double	horizontal_ray_distance;
	double	vertical_ray_distance;
	t_vec2	horizontal_ray_pos;
	t_vec2	vertical_ray_pos;
	double	tan_a;
	double	rad;

	ray->relat_angle = ray->persp_angle + game->player.angle;
	if (ray->relat_angle < 0)
		ray->relat_angle += 360;
	if (ray->relat_angle > 360)
		ray->relat_angle -= 360;
	if (fmod(ray->relat_angle, 45) == 0)
		ray->relat_angle += 0.000042;
	rad = ray->relat_angle * (RAD_ANG);
	tan_a = tan(rad);
	horizontal_ray_pos = horizontal_ray_calculator(game, rad, tan_a);
	vertical_ray_pos = vertical_ray_calculator(game, rad, tan_a);
	horizontal_ray_distance = distance(game->player.pos, horizontal_ray_pos);
	vertical_ray_distance = distance(game->player.pos, vertical_ray_pos);
	if (horizontal_ray_distance > vertical_ray_distance)
	{
		ray->pos = vertical_ray_pos;
		ray->dis = vertical_ray_distance;
		ray->v_h = 'v';
	}
	else
	{
		ray->pos = horizontal_ray_pos;
		ray->dis = horizontal_ray_distance;
		ray->v_h = 'h';
	}
}
