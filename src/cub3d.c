/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/14 13:46:36 by bdemirbu         ###   ########.fr       */
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

void	set_mlx(t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1); //free
	game->win = mlx_new_window(game->mlx,
			WINDOWS_WIDTH, WINDOWS_HEIGHT, "cub3d");
	if (!game->win)
		exit(1); //free
	game->images.background = create_new_image(game->mlx,
			WINDOWS_WIDTH, WINDOWS_HEIGHT);
	if (!game->images.background.image)
		exit(1); //free
	game->images.N = import_image(game->mlx, "jack2.xpm");
	if (!game->images.N.image)
		exit(1); // free
	game->images.S = import_image(game->mlx, "bmo.xpm");
	if (!game->images.S.image)
		exit(1); // free
	game->images.W = import_image(game->mlx, "finn.xpm");
	if (!game->images.W.image)
		exit(1); // free
	game->images.E = import_image(game->mlx, "gunter.xpm");
	if (!game->images.E.image)
		exit(1); // free
	game->player.pos.x = 650;
	game->player.pos.y = 750;
	game->player.angle = 270;
	game->shadow = 0;
	mlx_do_key_autorepeatoff(game->mlx);
}

int	main(void)
{
	t_cub3d	game;

	ft_memset(&game, 0, sizeof(t_cub3d));
	create_map(&game);
	set_mlx(&game);
	char **path;
	path = (char **)malloc(sizeof(char *) * 31);
	path[0] = "Portal00.xpm";
	path[1] = "Portal01.xpm";
	path[2] = "Portal02.xpm";
	path[3] = "Portal03.xpm";
	path[4] = "Portal04.xpm";
	path[5] = "Portal05.xpm";
	path[6] = "Portal06.xpm";
	path[7] = "Portal07.xpm";
	path[8] = "Portal08.xpm";
	path[9] = "Portal09.xpm";
	path[10] = "Portal10.xpm";
	path[11] = "Portal11.xpm";
	path[12] = "Portal12.xpm";
	path[13] = "Portal13.xpm";
	path[14] = "Portal14.xpm";
	path[15] = "Portal15.xpm";
	path[16] = "Portal16.xpm";
	path[17] = "Portal17.xpm";
	path[18] = "Portal18.xpm";
	path[19] = "Portal19.xpm";
	path[20] = "Portal20.xpm";
	path[21] = "Portal21.xpm";
	path[22] = "Portal22.xpm";
	path[23] = "Portal23.xpm";
	path[24] = "Portal24.xpm";
	path[25] = "Portal25.xpm";
	path[26] = "Portal26.xpm";
	path[27] = "Portal27.xpm";
	path[28] = "Portal28.xpm";
	path[29] = "Portal29.xpm";
	path[30] = NULL;
	game.images.Na = create_animate(&game, path);
	mlx_hook(game.win, 3, 1L << 0, key_up, &game);
	mlx_hook(game.win, 2, 1L << 1, key_down, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
