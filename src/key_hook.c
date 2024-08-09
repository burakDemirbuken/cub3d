/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by                   #+#    #+#             */
/*   Updated: 2024/08/09 15:48:55 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <stdlib.h>

int	key_down(int keycode, t_cub3d *game)
{
	if (keycode == KEY_LEFT)
		game->player.is_press_n_rotation = 1;
	if (keycode == KEY_RIGHT)
		game->player.is_press_p_rotation = 1;
	if (keycode == KEY_W)
		game->player.is_press_w = 1;
	if (keycode == KEY_A)
		game->player.is_press_a = 1;
	if (keycode == KEY_S)
		game->player.is_press_s = 1;
	if (keycode == KEY_D)
		game->player.is_press_d = 1;
	if (keycode == KEY_ESC)
		exit(1); // free
	if (keycode == KEY_G)
		game->shadow = !game->shadow;
	if (keycode == KEY_H)
	{
		printf("player x: %f\n", game->player.pos.x);
		printf("player y: %f\n", game->player.pos.y);
		printf("player angle: %f\n", game->player.angle);
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

/* int	mouse_click(int keycode, int x, int y, t_cub3d *game)
{
	if (keycode == 1)
	{
		if (!(x < 0 || y > MAP_HEIGHT * REC_HEIGHT || y < 0 || x > MAP_WIDTH * REC_WIDTH))
		{
			if (game->is_click == false)
			{
				game->is_click = true;
				game->click.y = y / REC_HEIGHT;
				game->click.x = x / REC_WIDTH;
				game->map.map[y / REC_HEIGHT][x / REC_WIDTH] = 0x0000FF00;
			}
			else
			{
				game->is_click = false;
				bresenham_line(game, game->click.x, game->click.y, x / REC_WIDTH, y / REC_HEIGHT, 0x00202020);
			}
		}
	}
	if (keycode == 2)
		if (!(x < 0 || y > MAP_HEIGHT * REC_HEIGHT || y < 0 || x > MAP_WIDTH * REC_WIDTH))
			game->map.map[y / REC_HEIGHT][x / REC_WIDTH] = 0x00252525;
	return (0);
} */
