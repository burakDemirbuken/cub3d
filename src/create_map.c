/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:20:52 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/27 10:44:51 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

void	draw_rectangle(t_image img, int x, int y, int width, int height,
							bool grid, int color)
{
	int		i_h;
	int		i_w;

	i_h = 0;
	while (i_h < height)
	{
		i_w = 0;
		while (i_w < width)
		{
			if (i_w + x < 1 || i_w + x > WINDOWS_WIDTH - 1
				|| i_h + y < 0 || i_h + y > WINDOWS_HEIGHT - 1)
			{
				i_w++;
				continue;
			}
			if (grid && (i_w == width - 1 || i_w == 0
				|| i_h == height - 1 || i_h == 0))
				*(unsigned int*)(img.data + (int)((y + i_h) * img.line_lenght
				+ (x + i_w) * (img.bits_per_pixel / 8))) = 0x00303030;
			else
				*(unsigned int*)(img.data + (int)((y + i_h) * img.line_lenght
				+ (x + i_w) * (img.bits_per_pixel / 8))) = color;
			i_w++;
		}
		i_h++;
	}
}

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
			if (game->map.map[y][x] != '1')
				color = 0x00080808;
			else
				color = 0x00808080;
			draw_rectangle(game->images.background, x * REC_WIDTH, y * REC_HEIGHT, REC_WIDTH, REC_HEIGHT, true, color);
			x++;
		}
		y++;
	}
	draw_player(game);
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
		game->map.map[y] = (char *)malloc(sizeof(char) * (MAP_WIDTH + 1));
		while (x < MAP_WIDTH)
		{
			if ( x == 0 || y == 0  || x == MAP_WIDTH - 1 || y == MAP_HEIGHT -1)
				game->map.map[y][x] = '1';
			else
				game->map.map[y][x] = '0';
			x++;
		}
		game->map.map[y][x] = 0;
		y++;
	}
	game->map.map[y] = 0;
	game->map.height = MAP_HEIGHT;
	game->map.width = MAP_WIDTH;
	game->map.map[7][3] = '1';
	game->map.map[6][9] = '1';
	game->map.map[3][4] = '1';
	game->map.map[4][5] = '1';
	game->map.map[4][3] = '1';
	game->map.map[5][4] = '1';
	game->map.map[3][1] = '1';
	game->map.map[7][4] = '1';
	game->map.map[2][1] = '1';
}
