/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:47:34 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/24 16:24:55 by bdemirbu         ###   ########.fr       */
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
			return (REC_HEIGHT - fmod(p_pos.y, REC_HEIGHT));
		else
			return (fmod(p_pos.y, REC_HEIGHT));
	}
	else if (v_h == 'v')
	{
		if (rad > M_PI_2 && rad < 3 * M_PI_2)
			return (fmod(p_pos.x, REC_WIDTH));
		else
			return (REC_WIDTH - fmod(p_pos.x, REC_WIDTH));
	}
	return (0.0f);
}
