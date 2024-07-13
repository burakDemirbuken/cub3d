/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:10:02 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/13 14:46:45 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
#include <stdlib.h>

// verilen x0,y0 kordinatından x1 y1 kordinatına doğru bir çizgi çeker.
void	bresenham_line(t_image img, int x0, int y0, int x1, int y1, int color)
{
	int	dx, dy, p, sx, sy;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	if (dx > dy)
	{
		p = 2 * dy - dx;
		while (x0 != x1 && x0 < REC_WIDTH * MAP_WIDHT && x0 > 0)
		{
			*(unsigned int*)(img.data + (int)((y0 * img.line_lenght)
				+ (x0 * img.bits_per_pixel / 8))) = color;
			x0 += sx;
			if (p > 0)
			{
				y0 += sy;
				p -= 2 * dx;
			}
			p += 2 * dy;
		}
	}
	else
	{
		p = 2 * dx - dy;
		while (y0 != y1 && y0 < REC_HEIGHT * MAP_HEIGHT && y0 > 0)
		{
			*(unsigned int*)(img.data + (int)(y0 * img.line_lenght + x0
				* (img.bits_per_pixel / 8))) = color;
			y0 += sy;
			if (p > 0)
			{
				x0 += sx;
				p -= 2 * dy;
			}
			p += 2 * dx;
		}
	}
}

t_vec2	rotate_around_point(t_vec2 point, t_vec2 pivot, double angle)
{
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

	draw_rectangle(game->images.background, game->player.pos.x - 10, game->player.pos.y - 10, 20, 20, false, 0x00FF0000);
	cor = rotate_around_point((t_vec2){game->player.pos.x + 10, game->player.pos.y}, game->player.pos, game->player.angle);
	bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, (int)cor.x, (int)cor.y, 0x0000FF00);
}
