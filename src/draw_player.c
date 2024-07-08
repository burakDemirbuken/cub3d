/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:10:02 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/08 23:11:27 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>


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
