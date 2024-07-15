/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/15 14:09:27 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_image	create_image(void *mlx, int width, int height)
{
	t_image	img;

	img.image = mlx_new_image(mlx, width, height);
	img.data = mlx_get_data_addr(img.image, &img.bits_per_pixel,
			&img.line_lenght, &img.endian);
	return (img);
}

void	set_mlx(t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(0);
	game->win = mlx_new_window(game->mlx, MAP_WIDHT * REC_WIDTH, MAP_HEIGHT * REC_HEIGHT, "naber müdür");
	if (!game->win)
		exit(0);
	game->images.background = create_image(game->mlx, REC_WIDTH * MAP_WIDHT, REC_HEIGHT * MAP_HEIGHT);
	game->images.floor = create_image(game->mlx, REC_WIDTH, REC_HEIGHT);
	game->images.wall = create_image(game->mlx, REC_HEIGHT, REC_HEIGHT);
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
