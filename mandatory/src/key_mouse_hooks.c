/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:01:40 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/23 18:12:24 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
 *	typedef struct s_cub3d t_cub3d
 *	#define KEY_W		13
 *	#define KEY_A		0
 *	#define KEY_S		1
 *	#define KEY_D		2
 *	#define KEY_ESC		53
 *	#define KEY_LEFT	123
 *	#define KEY_RIGHT	124
 *	#define KEY_G		5
 *	#define KEY_H		4
 *	void		end_program(t_cub3d *game, int e)
 */
#include <stdio.h>
/*
 *	int printf(const char *__restrict__, ...)
 */

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

