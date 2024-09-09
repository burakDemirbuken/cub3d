/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/09 11:08:16 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#ifdef __linux__
	#include "../../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../../includes/minilibx/mlx.h"
#endif
#include <stdlib.h>

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
		exit(1); // free
	else if (keycode == KEY_G)
		game->shadow = !game->shadow;
	else if (keycode == KEY_H)
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

int	mouse_down(int keycode, int x, int y, t_cub3d *game)
{
	(void)x;
	(void)y;
	if (keycode == 2)
	{
		game->mouse_control = !game->mouse_control;
		if (game->mouse_control == true)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	if (keycode == 1)
	{
		game->interact = true;
	}
	return (0);
}
