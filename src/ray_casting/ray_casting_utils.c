/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:47:34 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/28 15:12:34 by bkorkut          ###   ########.fr       */
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
