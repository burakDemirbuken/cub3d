/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:15:30 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:14:43 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

static bool	inside_map(t_cub3d *game, t_vec2 ret)
{
	if ((int)ret.x > (game->map.width * REC_WIDTH) - 1 || (int)ret.x < 1
		|| ret.y < 1 || ret.y > (game->map.height * REC_HEIGHT) - 1)
	{
		if ((int)ret.x > (game->map.width * REC_WIDTH) - 1)
			ret.x = (game->map.width * REC_WIDTH) - 1;
		if ((int)ret.x < 1)
			ret.x = 1;
		if (ret.y < 1)
			ret.y = 1;
		if (ret.y > (game->map.height * REC_HEIGHT) - 1)
			ret.y = (game->map.height * REC_HEIGHT) - 1;
		return (false);
	}
	return (true);
}

static void	ret_add(t_vec2 *ret, t_vec2 add, double rad)
{
	if (rad > M_PI_2 && rad < 3 * M_PI_2)
		ret->x -= add.x;
	else
		ret->x += add.x;
	if (rad > 0 && rad < M_PI)
		ret->y += add.y;
	else
		ret->y -= add.y;
}

static bool	hits_wall(t_cub3d *game, t_vec2 point, double rad, char v_h)
{
	if (v_h == 'v')
	{
		if (M_PI_2 < rad && rad < 3 * M_PI_2)
		{
			if (game->map.map[((int)point.y / REC_HEIGHT)]
				[((int)point.x / REC_WIDTH) - 1] == '1')
				return (true);
		}
		else if (game->map.map[((int)point.y / REC_HEIGHT)]
			[((int)point.x / REC_WIDTH)] == '1')
			return (true);
	}
	else if (v_h == 'h')
	{
		if (rad > 0 && rad < M_PI)
		{
			if (game->map.map[((int)point.y / REC_HEIGHT)]
				[((int)point.x / REC_WIDTH)] == '1')
				return (true);
		}
		else if (game->map.map[((int)point.y / REC_HEIGHT) - 1]
			[((int)point.x / REC_WIDTH)] == '1')
			return (true);
	}
	return (false);
}

t_vec2	vertical_ray_calculator(t_cub3d *game, double rad, double tan_a)
{
	t_vec2	ray_x;
	t_vec2	ret;

	ret = game->player.pos;
	if (rad == M_PI_2 || rad == 3 * M_PI_2)
		return (ret.y = __FLT_MAX__, ret);
	ray_x.x = get_offset(game->player.pos, rad, 'v');
	ray_x.y = ray_x.x * tan_a;
	if (ray_x.y < 0)
		ray_x.y *= -1;
	while (42)
	{
		ret_add(&ret, ray_x, rad);
		if (inside_map(game, ret) == false)
			return (ret);
		if (hits_wall(game, ret, rad, 'v') == true)
			return (ret);
		ray_x.x = (double)REC_WIDTH;
		ray_x.y = ray_x.x * tan_a;
		if (ray_x.y < 0)
			ray_x.y *= -1;
	}
	return (ret);
}

t_vec2	horizontal_ray_calculator(t_cub3d *game, double rad, double tan_a)
{
	t_vec2	ray_y;
	t_vec2	ret;

	ret = game->player.pos;
	if (rad == 0 || rad == M_PI)
		return (ret.x = __FLT_MAX__, ret);
	ray_y.y = get_offset(game->player.pos, rad, 'h');
	ray_y.x = ray_y.y / tan_a;
	if (ray_y.x < 0.0f)
		ray_y.x *= -1;
	while (42)
	{
		ret_add(&ret, ray_y, rad);
		if (inside_map(game, ret) == false)
			return (ret);
		if (hits_wall(game, ret, rad, 'h') == true)
			return (ret);
		ray_y.y = (double)REC_HEIGHT;
		ray_y.x = ray_y.y / tan_a;
		if (ray_y.x < 0)
			ray_y.x *= -1;
	}
	return (ret);
}
