/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:47:34 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/23 18:01:43 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
 *	#include <stdbool.h>
	-	#define bool _Bool
	-	#define false 0
	-	#define true 1
 *	typedef struct s_vec2	t_vec2
 *	typedef struct s_cub3d	t_cub3d
 *	#define M_PI_2		1.57079632679489661923132169163975144
 *	#define MATH_3PI_2	4.71238898038468985769396507491925432
 *	#define REC_HEIGHT	100
 *	#define REC_WIDTH	100
 *	# define NORTH	'N'
 *	# define SOUTH	'S'
 *	# define WEST	'W'
 *	# define EAST	'E'
 *	# define DOOR	'2'
 */
#include "libft/libft.h"
/*
 *	char	*ft_strchr(const char *s, int c)
 */
#include <math.h>
/*
 *	#define	M_PI 3.14159265358979323846264338327950288
 *	double	fmod(double, double)
 *	double	sqrt(double)
 */

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
		if (0.0 < rad && rad <= M_PI)
			return (REC_HEIGHT - fmod(p_pos.y, REC_HEIGHT));
		else
			return (fmod(p_pos.y, REC_HEIGHT));
	}
	else if (v_h == 'v')
	{
		if (M_PI_2 < rad && rad <= MATH_3PI_2)
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

char	hits_wall(t_cub3d *game, t_vec2 point, double rad, char v_h)
{
	int	y;
	int	x;

	x = (int)point.x / REC_WIDTH;
	y = (int)point.y / REC_HEIGHT;
	if (v_h == 'v' && M_PI_2 < rad && rad <= MATH_3PI_2)
		x -= 1;
	else if (v_h == 'h' && !(0 < rad && rad <= M_PI))
		y -= 1;
	if (game->map.map[y][x] == DOOR)
		return (DOOR);
	else if (ft_strchr("1M", game->map.map[y][x]) != 0)
	{
		if (v_h == 'v' && M_PI_2 < rad && rad <= MATH_3PI_2)
			return (WEST);
		else if (v_h == 'v' && !(M_PI_2 < rad && rad <= MATH_3PI_2))
			return (EAST);
		else if (v_h == 'h' && (0 < rad && rad <= M_PI))
			return (NORTH);
		else if (v_h == 'h' && !(0 < rad && rad <= M_PI))
			return (SOUTH);
	}
	return ('0');
}
