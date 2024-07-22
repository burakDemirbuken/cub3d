/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:47:34 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/22 20:48:32 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

float	distance(t_vec2 point1, t_vec2 point2)
{
	float	x;
	float	y;

	x = point1.x - point2.x;
	y = point1.y - point2.y;
	return (sqrt((x * x) + (y * y)));
}

float	get_offset(t_vec2 p_pos, float rad, char v_h)
{
	if (v_h == 'h')
	{
		if (0.0 < rad && rad < M_PI)
			return (((int)p_pos.y + REC_HEIGHT) / REC_HEIGHT
				* REC_HEIGHT - p_pos.y);
		else
			return (p_pos.y - ((int)p_pos.y / REC_HEIGHT) * REC_HEIGHT);
	}
	else if (v_h == 'v')
	{
		if (rad > M_PI_2 && rad < 3 * M_PI_2)
			return (p_pos.x - ((int)p_pos.x / REC_HEIGHT) * REC_HEIGHT);
		else
			return ((((int)p_pos.x + REC_WIDTH) / REC_WIDTH)
				* REC_WIDTH - p_pos.x);
	}
	return (0.0f);
}
