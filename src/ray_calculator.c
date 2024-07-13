/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:15:30 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/13 18:50:37 by bdemirbu         ###   ########.fr       */
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

t_vec2 y_ray_calculator(t_cub3d *game)
{
	t_vec2	ray_y;
	t_vec2	ret;
	float	rad;
	float	tan_a;

    ret = game->player.pos;
	if (game->player.angle == 0 || game->player.angle == 180)
		return (ret);
	rad = game->player.angle * (M_PI / 180.0);
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
        if ((int)ret.x > (MAP_WIDHT * REC_WIDTH) - 1 && (int)ret.x < 1)
            return (game->player.pos);
        if (rad > 0 && rad < M_PI)
        {
            if (game->map.map[((int)ret.y / REC_HEIGHT)][((int)ret.x / REC_WIDTH)] == '1')
                break ;
        }
        else if (game->map.map[((int)ret.y / REC_HEIGHT) + 1][((int)ret.x / REC_WIDTH)] == '1')
            break ;
        if (0.0 < rad && rad < M_PI)
            ray_y.y = -1 * REC_HEIGHTf;
        else
            ray_y.y = REC_HEIGHTf;
	    ray_y.x = ray_y.y / tan_a;
        if (ray_y.x < 0)
		    ray_y.x *= -1;
    }
    return (ret);
}
