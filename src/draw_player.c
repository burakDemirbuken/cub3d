/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:10:02 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/23 11:56:48 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
#include <stdlib.h>

// verilen x0,y0 kordinatından x1 y1 kordinatına doğru bir çizgi çeker.
void	bresenham_line(t_image img, int x0, int y0, int x1, int y1, int color)
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
			*(unsigned int*)(img.data
			+ (int)((y * img.line_lenght)
			+ (x * img.bits_per_pixel / 8))) = color;
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
			*(unsigned int*)(img.data
			+ (int)(y * img.line_lenght
			+ x * (img.bits_per_pixel / 8))) = color;
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

void	draw_player(t_cub3d *game)
{
	draw_rectangle(game->images.background, game->player.pos.x - 10, game->player.pos.y - 10, 20, 20, false, 0x00FF0000);
}
