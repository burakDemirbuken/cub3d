/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/08 11:06:33 by bdemirbu         ###   ########.fr       */
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
#include <stdio.h>

t_ray	ray_throw(t_cub3d *game, double angle)
{
	double	horizontal_ray_distance;
	double	vertical_ray_distance;
	t_vec2	horizontal_ray_pos;
	t_vec2	vertical_ray_pos;
	t_ray	ret;
	double	tan_a;
	double	rad;

	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	if (angle == 45.0 || angle == 135.0 || angle == 225.0 || angle == 315.0)
		angle += 0.000042;
	ret.angle = angle;
	rad = ret.angle * (RAD_CONVERT);
	tan_a = tan(rad);
	horizontal_ray_pos = horizontal_ray_calculator(game, rad, tan_a);
	vertical_ray_pos = vertical_ray_calculator(game, rad, tan_a);
	horizontal_ray_distance = distance(game->player.pos, horizontal_ray_pos);
	vertical_ray_distance = distance(game->player.pos, vertical_ray_pos);
	if (horizontal_ray_distance > vertical_ray_distance)
	{
		ret.pos = vertical_ray_pos;
		ret.dis = vertical_ray_distance;
		ret.v_h = 'v';
	}
	else
	{
		ret.pos = horizontal_ray_pos;
		ret.dis = horizontal_ray_distance;
		ret.v_h = 'h';
	}
	return (ret);
}

int	game_loop(t_cub3d	*game)
{
	update_player_status(game);
	display(game);
	//draw_map(game);
	//mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}

/*	mousenin olduğu kareyi belirlenen renge boyar.
 	#ifdef __linux__
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	#elif __APPLE__ || __MACH__
		mlx_mouse_get_pos(game->win, &x, &y);
	#endif
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDTH * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, REC_HEIGHT, REC_HEIGHT, true, 0x00808080); */
