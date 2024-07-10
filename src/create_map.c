/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:20:52 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/10 21:56:14 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

void	draw_map(t_cub3d *game)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == '1')
				draw_rectangle(game, x * REC_WIDTH, y * REC_HEIGHT, REC_WIDTH, REC_HEIGHT, true, 0x00808080);
			else
				draw_rectangle(game, x * REC_WIDTH, y * REC_HEIGHT, REC_WIDTH, REC_HEIGHT, true, 0x00080808);
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_cub3d *game, int x, int y, int width, int height, bool grid, int color)
{
	int		i_h;
	int		i_w;

	i_h = 0;
	while (i_h < height)
	{
		i_w = 0;
		while (i_w < width)
		{
			if (grid && (i_w == width - 1 || i_w == 0
				|| i_h == height - 1 || i_h == 0))
				*(unsigned int*)(game->images.background->data
				+ (int)((y + i_h) * game->images.background->line_lenght
				+		(x + i_w) * (game->images.bits_per_pixel / 8))) = 0x00303030;
			else
				*(unsigned int*)(game->images.background->data
				+ (int)((y + i_h) * game->images.background->line_lenght
				+		(x + i_w) * (game->images.bits_per_pixel / 8))) = color;
			i_w++;
		}
		i_h++;
	}
}

void	create_map(t_cub3d *game)
{
	int	x;
	int	y;

	game->map.map = (char **)malloc(sizeof(char *) * (MAP_HEIGHT + 1));
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		game->map.map[y] = (char *)malloc(sizeof(char) * (MAP_WIDHT + 1));
		while (x < MAP_WIDHT)
		{
			if ( x == 0 || y == 0  || x == MAP_WIDHT - 1 || y == MAP_HEIGHT -1)
				game->map.map[y][x] = '1';
			else
				game->map.map[y][x] = '0';
			x++;
		}
		game->map.map[y][x] = 0;
		y++;
	}
	game->map.map[y] = 0;
	game->map.map[4][6] = '1';
	game->map.map[2][7] = '1';
	game->map.map[5][6] = '1';
	game->map.map[5][4] = '1';
	game->map.map[1][7] = '1';
	game->map.map[5][8] = '1';
	game->map.map[3][7] = '1';
	game->map.map[1][3] = '1';
}
