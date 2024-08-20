/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:25:47 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/libft/libft.h"
#ifdef __linux__
	#include "../../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../../includes/minilibx/mlx.h"
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
	if (fmod(angle, 45) == 0)
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
