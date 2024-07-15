/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:15:30 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/15 14:01:46 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <math.h>
#include <unistd.h>


t_vec2 x_ray_calculator(t_cub3d *game, float angle);
t_vec2 y_ray_calculator(t_cub3d *game, float angle);
/*
void	y_one_ray_throw(t_cub3d *game)
{
	t_vec2  new_point;
	float   x;
	float   y;

	if (0.0 < game->y.rad && game->y.rad < M_PI)
		y = (((int)game->player.pos.y + REC_HEIGHT) / REC_HEIGHT) * REC_HEIGHT - game->player.pos.y;
	else
		y = game->player.pos.y - ((int)game->player.pos.y / REC_HEIGHT) * REC_HEIGHT;
	x = y / game->y.tan;
	if (x < 0)
		x *= -1;

	if (game->y.rad > M_PI_2 && game->y.rad < 3 * M_PI_2)
		new_point.x = game->player.pos.x - x;
	else
		new_point.x = game->player.pos.x + x;
	if (game->y.rad > 0 && game->y.rad < M_PI)
		new_point.y = game->player.pos.y + y;
	else
		new_point.y = game->player.pos.y - y;

	printf("x: %f,y: %f, angele: %f\n", new_point.x, new_point.y, game->player.angle);
	if ((int)new_point.x < (MAP_WIDHT * REC_WIDTH) - 1 && (int)new_point.x > 1) {
		bresenham_line(game->images.background, (int)game->player.pos.x,
					   (int)game->player.pos.y, (int)new_point.x, (int)new_point.y, 0x00FFFF23);
	}
}
*/

float   distance(t_vec2 point1,t_vec2  point2)
{
	float   x;
	float   y;

	x = point1.x - point2.x;
	y = point1.y - point2.y;
	return (sqrt((x * x) + (y * y)));
}


t_vec2  ret_add(t_vec2 ret,t_vec2 add, float rad)
{
    if (rad > M_PI_2 && rad < 3 * M_PI_2)
		ret.x -= add.x;
	else
		ret.x += add.x;
	if (rad > 0 && rad < M_PI)
		ret.y += add.y;
	else
		ret.y -= add.y;
    return (ret);
}

/* t_vec2  one_throw_ray(t_cub3d *game)
{
	t_vec2	ray_x;
	t_vec2	ret_x;
	t_vec2	ray_y;
	t_vec2	ret_y;
	float	rad;
	float	tan_a;

	ret_x = game->player.pos;
	ret_y = game->player.pos;
 	if ((game->player.angle) == 90 || (game->player.angle) == 270)
		return (ret);
	rad = (game->player.angle) * (M_PI / 180.0);
	tan_a = tan(rad);

	// vertical
	if (rad > M_PI_2 && rad < 3 * M_PI_2)
		ray_x.x = game->player.pos.x - ((int)game->player.pos.x / REC_WIDTH) * REC_WIDTH;
	else
		ray_x.x = (((int)game->player.pos.x + REC_WIDTH) / REC_WIDTH) * REC_WIDTH - game->player.pos.x;
	ray_x.y = ray_x.x * tan_a;
	if (ray_x.y < 0)
		ray_x.y *= -1;

	// horizontal
	if (0.0 < rad && rad < M_PI)
		ray_y.y = (((int)game->player.pos.y + REC_HEIGHT) / REC_HEIGHT) * REC_HEIGHT - game->player.pos.y;
	else
		ray_y.y = game->player.pos.y - ((int)game->player.pos.y / REC_HEIGHT) * REC_HEIGHT;
	ray_y.x = ray_y.y / tan_a;
	if (ray_y.x < 0)
		ray_y.x *= -1;

        // vertical
    ret_x = ret_add(ret_x, ray_x, rad);

    //  horizontal
    ret_x = ret_add(ret_y, ray_y, rad);
	while (42)
	{

    if ((int)ret_x.x > (MAP_WIDHT * REC_WIDTH) - 1 || (int)ret_x.x < 1 || ret_x.y < 1 || ret_x.y > (MAP_HEIGHT * REC_HEIGHT) - 1)
        return (game->player.pos);
    if ((int)ret_y.x > (MAP_WIDHT * REC_WIDTH) - 1 || (int)ret_y.x < 1 || ret_y.y < 1 || ret_y.y > (MAP_HEIGHT * REC_HEIGHT) - 1)
        return (game->player.pos);

        //  vertical
		if (M_PI_2 < rad && rad < 3 * M_PI_2)
		{
			if  (game->map.map[((int)ret_x.y / REC_HEIGHT)][((int)ret_x.x / REC_WIDTH) - 1] == '1')
				break ;
		}
		else if (game->map.map[((int)ret_x.y / REC_HEIGHT)][((int)ret_x.x / REC_WIDTH)] == '1')
			break ;
		ray_x.x = REC_WIDTHf;
		ray_x.y = ray_x.x * tan_a;
		if (ray_x.y < 0)
			ray_x.y *= -1;

		//  horizontal
		if (rad > 0 && rad < M_PI)
		{
			if  (game->map.map[((int)ret_y.y / REC_HEIGHT)][((int)ret_y.x / REC_WIDTH)] == '1')
				break ;
		}
		else if (game->map.map[((int)ret_y.y / REC_HEIGHT) - 1][((int)ret_y.x / REC_WIDTH)] == '1')
			break ;
		ray_y.y = REC_HEIGHTf;
		ray_y.x = ray_y.y / tan_a;
		if (ray_y.x < 0)
			ray_y.x *= -1;

        // vertical
        ret_x = ret_add(ret_x, ray_x, rad);

        //  horizontal
        ret_x = ret_add(ret_y, ray_y, rad);

	}
	return (ret);
} */

t_vec2 x_ray_calculator(t_cub3d *game, float angle)
{
	t_vec2	ray_x;
	t_vec2	ret;
	float	rad;
	float	tan_a;

	ret = game->player.pos;
	if ((angle) == 90 || (angle) == 270)
		return (y_ray_calculator(game, angle));
	rad = (angle) * (M_PI / 180.0);
	tan_a = tan(rad);
	if (rad > M_PI_2 && rad < 3 * M_PI_2)
		ray_x.x = game->player.pos.x - ((int)game->player.pos.x / REC_HEIGHT) * REC_HEIGHT;
	else
		ray_x.x = (((int)game->player.pos.x + REC_WIDTH) / REC_WIDTH) * REC_WIDTH - game->player.pos.x;
	ray_x.y = ray_x.x * tan_a;
	if (ray_x.y < 0)
		ray_x.y *= -1;
	while (42)
	{
		if (rad > M_PI_2 && rad < 3 * M_PI_2)
			ret.x -= ray_x.x;
		else
			ret.x += ray_x.x;
		if (rad > 0 && rad < M_PI)
			ret.y += ray_x.y;
		else
			ret.y -= ray_x.y;
		if ((int)ret.x > (MAP_WIDHT * REC_WIDTH) - 1 || (int)ret.x < 1 || ret.y < 1 || ret.y > (MAP_HEIGHT * REC_HEIGHT) - 1)
        {
            if ((int)ret.x > MAP_WIDHT * REC_WIDTH)
                ret.x = MAP_WIDHT * REC_WIDTH;
            if ((int)ret.x < 0)
                ret.x = 0;
            if (ret.y < 0)
                ret.y = 0;
            if (ret.y > MAP_HEIGHT * REC_HEIGHT)
                ret.y = MAP_HEIGHT * REC_HEIGHT;
			return (ret);
        }
		if (M_PI_2 < rad && rad < 3 * M_PI_2)
		{
			if  (game->map.map[((int)ret.y / REC_HEIGHT)][((int)ret.x / REC_WIDTH) - 1] == '1')
				break ;
		}
		else if (game->map.map[((int)ret.y / REC_HEIGHT)][((int)ret.x / REC_WIDTH)] == '1')
			break ;
		ray_x.x = REC_WIDTHf;
		ray_x.y = ray_x.x * tan_a;
		if (ray_x.y < 0)
			ray_x.y *= -1;
	}
	return (ret);
}

t_vec2 y_ray_calculator(t_cub3d *game, float angle)
{
	t_vec2	ray_y;
	t_vec2	ret;
	float	rad;
	float	tan_a;

	ret = game->player.pos;
	if (angle == 0 || angle == 180)
		return (x_ray_calculator (game, angle));
	rad = angle * (M_PI / 180.0);
	tan_a = tan(rad);
	if (0.0 < rad && rad < M_PI)
		ray_y.y = (((int)game->player.pos.y + REC_HEIGHT) / REC_HEIGHT) * REC_HEIGHT - game->player.pos.y;
	else
		ray_y.y = game->player.pos.y - ((int)game->player.pos.y / REC_HEIGHT) * REC_HEIGHT;
	ray_y.x = ray_y.y / tan_a;
	if (ray_y.x < 0)
		ray_y.x *= -1;
	while (42)
	{
		if (rad > M_PI_2 && rad < 3 * M_PI_2)
			ret.x -= ray_y.x;
		else
			ret.x += ray_y.x;
		if (rad > 0 && rad < M_PI)
			ret.y += ray_y.y;
		else
			ret.y -= ray_y.y;
		if ((int)ret.x > (MAP_WIDHT * REC_WIDTH) - 1 || (int)ret.x < 1 || ret.y < 1 || ret.y > (MAP_HEIGHT * REC_HEIGHT) - 1)
        {
            if ((int)ret.x > (MAP_WIDHT * REC_WIDTH) - 1)
                ret.x = (MAP_WIDHT * REC_WIDTH) - 1;
            if ((int)ret.x < 1)
                ret.x = 1;
            if (ret.y < 1)
                ret.y = 1;
            if (ret.y > (MAP_HEIGHT * REC_HEIGHT) - 1)
                ret.y = (MAP_HEIGHT * REC_HEIGHT) - 1;
			return (ret);
        }
		if (rad > 0 && rad < M_PI)
		{
			if  (game->map.map[((int)ret.y / REC_HEIGHT)][((int)ret.x / REC_WIDTH)] == '1')
				break ;
		}
		else if (game->map.map[((int)ret.y / REC_HEIGHT) - 1][((int)ret.x / REC_WIDTH)] == '1')
			break ;
		ray_y.y = REC_HEIGHTf;
		ray_y.x = ray_y.y / tan_a;
		if (ray_y.x < 0)
			ray_y.x *= -1;

	}
	return (ret);
}
