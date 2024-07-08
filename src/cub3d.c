/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/08 23:11:48 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <stdio.h>

void	set_mlx(t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(0);
	game->win = mlx_new_window(game->mlx, MAP_WIDHT * REC_WIDTH, MAP_HEIGHT * REC_HEIGHT, "naber müdür");
	if (!game->win)
		exit(0);
	game->background = mlx_new_image(game->mlx,  MAP_WIDHT * REC_WIDTH, MAP_HEIGHT * REC_HEIGHT);
	game->addr.canvas = mlx_get_data_addr(game->background, &game->addr.bits_per_pixel, &game->addr.line_lenght, &game->addr.endian);
	game->player.pos.x = MAP_WIDHT * REC_WIDTH / 2;
	game->player.pos.y = MAP_HEIGHT * REC_HEIGHT / 2;
	game->player.angle = 45;
}

int	main()
{
	t_cub3d	game;
	int		y;
	int		x;

	ft_memset(&game, 0, sizeof(t_cub3d));
	create_map(&game);
	set_mlx(&game);
	draw_map(&game);
	draw_player(&game);

	mlx_hook(game.win, 3, 1L << 0, key_up, &game);
	mlx_hook(game.win, 2, 1L << 1, key_down, &game);
	// mlx_mouse_hook(game.win, mouse_click, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

