/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/01 20:12:09 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include "../include/minilibx/mlx.h"
#include <stdio.h>

#define HEİGHT 100
#define WİDHT 100

static int	key_down(int keycode, t_cub3d *game)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 13 || keycode == 126)
		game->player.is_press_w = 1;
	if (keycode == 0 || keycode == 123)
		game->player.is_press_a = 1;
	if (keycode == 1 || keycode == 125)
		game->player.is_press_s = 1;
	if (keycode == 2 || keycode == 124)
		game->player.is_press_d = 1;
	return (0);
}

static int	key_up(int keycode, t_cub3d *game)
{
	exit(0);
	if (keycode == 13 || keycode == 126)
		game->player.is_press_w = 0;
	if (keycode == 0 || keycode == 123)
		game->player.is_press_a = 0;
	if (keycode == 1 || keycode == 125)
		game->player.is_press_s = 0;
	if (keycode == 2 || keycode == 124)
		game->player.is_press_d = 0;
	return (0);
}

void	draw_rectangle(t_cub3d *game, t_vec2 pos, int height, int widht, int color)
{

}

void	draw_map(t_cub3d *game)
{

}

int	game_loop(t_cub3d	*game)
{
	return (0);
}
int	main()
{
	t_cub3d	game;

	ft_memset(&game, 0, sizeof(t_cub3d));
	game.player.pos.x = 5;
	game.player.pos.x = 6;
	game.map.map = (char **)malloc(sizeof(char *) * 11);
	game.map.map[0] = ft_strdup("1111111111");
	game.map.map[1] = ft_strdup("1000000001");
	game.map.map[2] = ft_strdup("1000000001");
	game.map.map[3] = ft_strdup("1000000001");
	game.map.map[4] = ft_strdup("1000000001");
	game.map.map[5] = ft_strdup("1000000001");
	game.map.map[6] = ft_strdup("1000000001");
	game.map.map[7] = ft_strdup("1000000001");
	game.map.map[8] = ft_strdup("1000000001");
	game.map.map[9] = ft_strdup("1111111111");
	game.map.map[10] = NULL;
	game.map.height = ft_strlen(*game.map.map);
	game.map.widht = ft_strlen(game.map.map[0]);

	t_vec2	vec;
	int		x;
	int		y;
	int		color;
	int		i_w;
	int		i_h;

	game.mlx = mlx_init();
	if (!game.mlx)
		exit(0);
	game.win = mlx_new_window(game.mlx, game.map.height * HEİGHT, game.map.widht * WİDHT, "naber müdür");
	if (!game.win)
		exit(0);
	y = 0;
	while (y < game.map.height)
	{
		x = 0;
		while (x < game.map.widht)
		{
			vec.x = x * WİDHT;
			vec.y = y * HEİGHT;
			if (game.map.map[y][x] == '1')
				color = 0x45000FFF;
			else
				color = 0x45FF0000;
			i_h = 0;
			while (i_h < HEİGHT)
			{
				i_w = 0;
				while (i_w < WİDHT)
				{
					mlx_pixel_put(game.mlx, game.win, vec.x + i_w, vec.y + i_h, color);
					i_w++;
				}
				i_h++;
			}
			x++;
		}
		y++;
	}
	void	*knk = mlx_new_image(game.mlx, game.map.height * HEİGHT, game.map.widht * WİDHT);
	mlx_get_data_addr(knk, )
	mlx_hook(game.win, 3, 0, key_up, &game);
	mlx_hook(game.win, 2, 0, key_down, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
