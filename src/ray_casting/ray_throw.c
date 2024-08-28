/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_throw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:31:32 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/28 15:45:39 by bkorkut          ###   ########.fr       */
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
	double	h_dis;
	double	v_dis;
	t_vec2	horizontal_ray_pos;
	t_vec2	vertical_ray_pos;
	double	tan_a;

	// this is in radians now..?
	// if (fmod(ray->relat_angle, 45) == 0)
		// ray->relat_angle += 0.000042;
	if (fmod(ray->relat_angle, M_PI_2 / 2) == 0)
		ray->relat_angle += RAD_ANG * 0.000042;
	tan_a = tan(ray->relat_angle);
	horizontal_ray_pos = horizontal_ray_calculator(game, ray->relat_angle, tan_a);
	vertical_ray_pos = vertical_ray_calculator(game, ray->relat_angle, tan_a);
	h_dis = distance(game->player.pos, horizontal_ray_pos);
	v_dis = distance(game->player.pos, vertical_ray_pos);
	if (h_dis > v_dis)
	{
		ray->pos = vertical_ray_pos;
		ray->dis = v_dis;
		ray->v_h = 'v';
	}
	else
	{
		ray->pos = horizontal_ray_pos;
		ray->dis = h_dis;
		ray->v_h = 'h';
	}
}
