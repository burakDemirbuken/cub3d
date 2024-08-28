/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:31:32 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/28 18:15:03 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// typedef t_cub3d;
// typedef t_ray;
// typedef t_vec2;
#include <math.h>
// tan();

void	cast_ray(t_cub3d *game, t_ray *ray)
{
	double	h_dis;
	double	v_dis;
	t_vec2	horizontal_ray_pos;
	t_vec2	vertical_ray_pos;
	double	tan_a;

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
	ray->dis *= cos(ray->persp_angle);
}
