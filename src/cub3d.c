/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/08 22:52:00 by bdemirbu         ###   ########.fr       */
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
#include <math.h>
#include <unistd.h>

// verilen x0,y0 kordinatından x1 y1 kordinatına doğru bir çizgi çeker.
void	bresenham_line(t_cub3d *game, int x0, int y0, int x1, int y1, int color)
{
	int	dx, dy, p, x, y;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	x = x0;
	y = y0;

	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	if (dx > dy)
	{
		p = 2 * dy - dx;
		while (x != x1)
		{
			*(unsigned int*)(game->addr.canvas + (int)((y * game->addr.line_lenght) + (x * game->addr.bits_per_pixel / 8))) = color;
			x += sx;
			if (p > 0)
			{
				y += sy;
				p -= 2 * dx;
			}
			p += 2 * dy;
		}
	}
	else
	{
		p = 2 * dx - dy;
		while (y != y1)
		{
			*(unsigned int*)(game->addr.canvas + (int)(y * game->addr.line_lenght + x * (game->addr.bits_per_pixel / 8))) = color;
			y += sy;
			if (p > 0)
			{
				x += sx;
				p -= 2 * dy;
			}
			p += 2 * dx;
		}
	}

}

// Rotasyon fonksiyonu

t_vec2	rotate_around_point(t_vec2 point, t_vec2 pivot, double angle) {
	t_vec2	new_point;

	double rad = angle * (M_PI / 180.0);
	double temp_x = point.x - pivot.x;
	double temp_y = point.y - pivot.y;
	double rotated_x = temp_x * cos(rad) - temp_y * sin(rad);
	double rotated_y = temp_x * sin(rad) + temp_y * cos(rad);
	new_point.x = rotated_x + pivot.x;
	new_point.y = rotated_y + pivot.y;

	return new_point;
}

void	draw_player(t_cub3d *game)
{
	t_vec2 cor;

	draw_rectangle(game, game->player.pos.x - 10, game->player.pos.y - 10, 20, 20, false, 0x00FF0000);
	cor = rotate_around_point((t_vec2){game->player.pos.x + 100, game->player.pos.y}, game->player.pos, game->player.angle);
	bresenham_line(game, (int)game->player.pos.x, (int)game->player.pos.y, (int)cor.x, (int)cor.y, 0x0000FF00);

}

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

