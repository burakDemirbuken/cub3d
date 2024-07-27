/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/27 14:58:46 by bdemirbu         ###   ########.fr       */
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

int	game_loop(t_cub3d	*game)
{
	double		horizontal_ray_distance;
	double		vertical_ray_distance;
	t_vec2		horizontal_ray_pos;
	t_vec2		vertical_ray_pos;
	double		i;
	int			a;
	double		rad;
	double		tan_a;

	update_player_status(game);

	i = 0;
	a = 0;

	while (a < RAY_COUNT)
	{
		game->rays[a].angle = game->player.angle + i - (PERSPECTIVE / 2.0);
		if (game->rays[a].angle < 0)
			game->rays[a].angle += 360;
		if (game->rays[a].angle > 360)
			game->rays[a].angle -= 360;
		if (game->rays[a].angle == 45.0 || game->rays[a].angle == 135.0 || game->rays[a].angle == 225.0 || game->rays[a].angle == 315.0)
			game->rays[a].angle += 0.000042;
		rad = game->rays[a].angle * (M_PI / 180.0);
		tan_a = tan(rad);
		horizontal_ray_pos = horizontal_ray_calculator(game, rad, tan_a);
		vertical_ray_pos = vertical_ray_calculator(game, rad, tan_a);
		horizontal_ray_distance = distance(game->player.pos, horizontal_ray_pos);
		vertical_ray_distance = distance(game->player.pos, vertical_ray_pos);
		if (horizontal_ray_distance > vertical_ray_distance)
		{
			game->rays[a].pos = vertical_ray_pos;
			game->rays[a].dis = vertical_ray_distance;
			game->rays[a].v_h = 'v';
		}
		else
		{
			game->rays[a].pos = horizontal_ray_pos;
			game->rays[a].dis = horizontal_ray_distance;
			game->rays[a].v_h = 'h';
		}
		//bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, (int)game->rays[a].pos.x, (int)game->rays[a].pos.y, 0x00FFFF23);
		i += PERSPECTIVE / RAY_COUNT;
		a++;
	}
	display(game);
	draw_map(game);
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
