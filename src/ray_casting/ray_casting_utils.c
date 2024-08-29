/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:47:34 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/29 15:36:16 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

double	distance(t_vec2 point1, t_vec2 point2)
{
	double	x;
	double	y;

	x = point1.x - point2.x;
	y = point1.y - point2.y;
	return (sqrt((x * x) + (y * y)));
}

double	get_offset(t_vec2 p_pos, double rad, char v_h)
{
	if (v_h == 'h')
	{
		if (0.0 < rad && rad < M_PI)
			return (REC_HEIGHT - fmod(p_pos.y, REC_HEIGHT));
		else
			return (fmod(p_pos.y, REC_HEIGHT));
	}
	else if (v_h == 'v')
	{
		if (rad > M_PI_2 && rad < MATH_3PI_2)
			return (fmod(p_pos.x, REC_WIDTH));
		else
			return (REC_WIDTH - fmod(p_pos.x, REC_WIDTH));
	}
	return (0.0);
}

bool	inside_map(t_cub3d *game, t_vec2 ret)
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

void	ret_add(t_vec2 *ret, t_vec2 add, double rad)
{
	if (rad > M_PI_2 && rad < MATH_3PI_2)
		ret->x -= add.x;
	else
		ret->x += add.x;
	if (rad > 0 && rad < M_PI)
		ret->y += add.y;
	else
		ret->y -= add.y;
}

bool	hits_wall(t_cub3d *game, t_vec2 point, double rad, char v_h)
{
	if (v_h == 'v')
	{
		if (M_PI_2 < rad && rad < MATH_3PI_2)
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
