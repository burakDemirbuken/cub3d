/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:01:40 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 15:57:47 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/minilibx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int	key_down(int keycode, t_cub3d *game)
{
	if (keycode == KEY_LEFT)
		game->player.is_press_n_rotation = 1;
	else if (keycode == KEY_RIGHT)
		game->player.is_press_p_rotation = 1;
	else if (keycode == KEY_W)
		game->player.is_press_w = 1;
	else if (keycode == KEY_A)
		game->player.is_press_a = 1;
	else if (keycode == KEY_S)
		game->player.is_press_s = 1;
	else if (keycode == KEY_D)
		game->player.is_press_d = 1;
	else if (keycode == KEY_ESC)
		end_program(game, 0);
	else if (keycode == KEY_G)
		game->shadow = !game->shadow;
	else if (keycode == KEY_H)
	{
		printf("player x: %f\n", game->player.pos.x);
		printf("player y: %f\n", game->player.pos.y);
		printf("player angle: %f\n", game->player.angle);
		printf("ray dist: %f\n", game->rays[RAY_COUNT / 2].dis);
	}
	return (0);
}

int	key_up(int keycode, t_cub3d *game)
{
	if (keycode == KEY_LEFT)
		game->player.is_press_n_rotation = 0;
	if (keycode == KEY_RIGHT)
		game->player.is_press_p_rotation = 0;
	if (keycode == KEY_W)
		game->player.is_press_w = 0;
	if (keycode == KEY_A)
		game->player.is_press_a = 0;
	if (keycode == KEY_S)
		game->player.is_press_s = 0;
	if (keycode == KEY_D)
		game->player.is_press_d = 0;
	return (0);
}

static void	mouse_left(int x, int y, t_cub3d *game)
{
	t_ray	ray;

	ray = game->rays[(int)(RAY_COUNT / 2)];
	y = (ray.pos.y / REC_WIDTH);
	x = (ray.pos.x / REC_WIDTH);
	if (ray.v_h == 'v' && M_PI_2 < game->player.angle
		&& game->player.angle <= MATH_3PI_2)
		x -= 1;
	else if (ray.v_h == 'h'
		&& !(game->player.angle > 0 && game->player.angle <= M_PI))
		y -= 1;
	if (ray.hit == DOOR && ray.dis < 150 && game->door_time == -1)
	{
		game->map.map[y][x] = '3';
		game->track_door[0] = y;
		game->track_door[1] = x;
		game->door_time = my_system_time();
	}
	else if (game->map.map[y][x] == '1' && game->map.map[y + 1][x] != 'M'
		&& game->map.map[y - 1][x] != 'M' && game->map.map[y][x + 1] != 'M'
		&& game->map.map[y][x - 1] != 'M')
		game->map.map[y][x] = '0';
}

static void	mouse_right(int x, int y, t_cub3d *game)
{
	t_ray	ray;

	ray = game->rays[(int)(RAY_COUNT / 2)];
	y = (ray.pos.y / REC_WIDTH);
	x = (ray.pos.x / REC_WIDTH);
	if (ray.v_h == 'v' && !(M_PI_2 < game->player.angle
			&& game->player.angle <= MATH_3PI_2))
		x -= 1;
	else if (ray.v_h == 'h'
		&& (game->player.angle > 0 && game->player.angle <= M_PI))
		y -= 1;
	if (ray.dis > REC_HEIGHT && game->map.map[y][x] == '0')
		game->map.map[y][x] = '1';
}

int	mouse_hook(int keycode, int x, int y, t_cub3d *game)
{
	if (keycode == 3)
	{
		game->mouse_control = !game->mouse_control;
		if (game->mouse_control == true)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	else if (keycode == 1)
		mouse_right(x, y, game);
	else if (keycode == 2)
		mouse_left(x, y, game);
	return (0);
}
