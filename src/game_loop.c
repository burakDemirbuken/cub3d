/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/10 23:08:25 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <math.h>
#include <stdio.h>

void	horizontal_ray_throw(t_cub3d *game)
{
	int	i;

	i = 0;
	int a = REC_WIDTH - (int)game->player.pos.x % REC_WIDTH;
	while (game->map.map[((int)game->player.pos.y) / REC_HEIGHT]
		[(int)(game->player.pos.x + (i * REC_WIDTH))/ REC_WIDTH] != '1')
		i++;
	bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y,
		(int)game->player.pos.x + a + ((i - 1) * REC_WIDTH), (int)game->player.pos.y, 0x00FFFF00);
}

void	update_player_status(t_cub3d *game)
{
	if (game->player.is_press_w && game->player.pos.y > 3.0f)
		game->player.pos.y -= 3.0f;
	if (game->player.is_press_s && game->player.pos.y < MAP_HEIGHT * REC_HEIGHT - 3.0f)
		game->player.pos.y += 3.0f;
	if (game->player.is_press_d && game->player.pos.x < MAP_WIDHT * REC_WIDTH - 3.0f)
		game->player.pos.x += 3.0f;
	if (game->player.is_press_a && game->player.pos.x > 3.0f)
		game->player.pos.x -= 3.0f;
	if (game->player.is_press_p_totation)
	{
		game->player.angle += 3.0F;
		if (game->player.angle > 360)
			game->player.angle = 0;
	}
	if (game->player.is_press_n_totation)
	{
		game->player.angle -= 3.0F;
		if (game->player.angle < 0)
			game->player.angle = 360;
	}
}

int	game_loop(t_cub3d	*game)
{
	update_player_status(game);
	draw_map(game);
	draw_player(game);
	horizontal_ray_throw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}

/*	mousenin olduğu kareyi belirlenen renge boyar.
 	#ifdef __linux__
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	#elif __APPLE__ || __MACH__
		mlx_mouse_get_pos(game->win, &x, &y);
	#endif
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDHT * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, REC_HEIGHT, REC_HEIGHT, true, 0x00808080); */
