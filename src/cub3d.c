/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/08 18:07:19 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
# include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
# include "../include/minilibx/mlx.h"
#endif
#include <stdlib.h>

t_image	create_new_image(void *mlx, int width, int height)
{
	t_image	img;

	ft_memset(&img, 0, sizeof(t_image));
	img.image = mlx_new_image(mlx, width, height);
	if (!img.image)
		return (img);
	img.data = mlx_get_data_addr(img.image, &img.bits_per_pixel,
			&img.line_lenght, &img.endian);
	img.height = height;
	img.width = width;
	return (img);
}

t_image	import_image(void *mlx, char *path)
{
	t_image	img;

	ft_memset(&img, 0, sizeof(t_image));
	img.image = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.image)
		return (img);
	img.data = mlx_get_data_addr(img.image, &img.bits_per_pixel,
			&img.line_lenght, &img.endian);
	return (img);
}

void	set_mlx(t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(0); //free
	game->win = mlx_new_window(game->mlx,
			WINDOWS_WIDTH, WINDOWS_HEIGHT, "cub3d");
	if (!game->win)
		exit(0); //free
	//mlx_mouse_hide(game->mlx, game->win);
	game->images.background = create_new_image(game->mlx,
			WINDOWS_WIDTH, WINDOWS_HEIGHT);
	if (!game->images.background.image)
		exit(0); //free
	game->images.N = import_image(game->mlx, "jack2.xpm");
	game->images.S = import_image(game->mlx, "bmo.xpm");
	game->images.W = import_image(game->mlx, "finn.xpm");
	game->images.E = import_image(game->mlx, "gunter.xpm");
	game->player.pos.x = 650;
	game->player.pos.y = 750;
	// game->player.pos.y = player_map_y * REC_HEIGHT - (REC_HEIGHT / 2);
	game->player.angle = 270;
	game->shadow = 1;
	mlx_do_key_autorepeatoff(game->mlx);
}

// need mlx pointer
// need av[1]

int	main(int ac, char **av)
{
	t_cub3d	game;

	if (ac == 2)
	{
		// NEEEM CHANGEE!!
		configure_level(&game, av[1]);
		// ft_memset(&game, 0, sizeof(t_cub3d));
		// create_map(&game);
		// set_mlx(&game);
		// draw_map(&game);
		// draw_player(&game);
		// mlx_hook(game.win, 3, 1L << 0, key_up, &game);
		// mlx_hook(game.win, 2, 1L << 1, key_down, &game);

		// mlx_mouse_hook(game.win, mouse_click, &game);
		// mlx_loop_hook(game.mlx, game_loop, &game);
		// mlx_loop(game.mlx);
	}
	else
		ft_putstr_fd("Expected a map.\n", 2);
	// return (1);
}
