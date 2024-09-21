/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:22:17 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 11:06:38 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/libft/libft.h"
#include <math.h>

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
				continue ;
			}
			if (grid && (i_w == width - 1 || i_w == 0
					|| i_h == height - 1 || i_h == 0))
				put_pixel_to_image(img, x + i_w, y + i_h, 0x00303030);
			else
				put_pixel_to_image(img, x + i_w, y + i_h, color);
			i_w++;
		}
		i_h++;
	}
}

//!
void	draw_circle(t_cub3d *game, int x, int y, int radius)
{
	int	cy;
	int	cx;

	cy = -radius;
	while (cy <= radius)
	{
		cx = -radius;
		while (cx <= radius)
		{
			if (!(cx * cx + cy * cy < radius * radius))
				put_pixel_to_image(game->images.minimap,
					cx + x, cy + y, 0xFF000000);
			cx++;
		}
		cy++;
	}
}

void	mini_map(t_cub3d *game)
{
	t_vec2			offset;
	unsigned int	color;
	int				map_height;
	int				map_width;
	int				x;
	int				y;

	map_height = 0;
	offset.x = fmod(game->player.pos.y, REC_WIDTH) / 4;
	offset.y = fmod(game->player.pos.x, REC_HEIGHT) / 4;
	while (map_height < 11)
	{
		map_width = 0;
		y = ((int)(game->player.pos.y / REC_HEIGHT)) + map_height - 5;
		while (map_width < 11)
		{
			x = ((int)(game->player.pos.x / REC_WIDTH)) + map_width - 5;
			if (0 <= x && x < game->map.width && 0 <= y && y < game->map.height
				&& ft_strchr("0123",game->map.map[y][x]) != NULL)
			{
				if (game->map.map[y][x] == '1')
					color = 0x10743224;
				else if (game->map.map[y][x] == '2')
					color = 0x10435231;
				else if (game->map.map[y][x] == '3')
					color = 0x10204693;
				else
					color = 0x10236412;
				draw_rectangle(game->images.minimap, (map_height * 25) - offset.x,
					(map_width * 25) - offset.y, 25, 25, true, color);
			}
			else
				draw_rectangle(game->images.minimap, (map_height * 25) - offset.x,
					(map_width * 25) - offset.y, 25, 25, false, 0x10000000);
			map_width++;
		}
		map_height++;
	}
	draw_circle(game, 125, 125, 125);
	draw_rectangle(game->images.minimap, (game->images.minimap.width / 2) - 1,
		(game->images.minimap.height / 2) - 1, 3, 3, false, 0x00FF0000);
	draw_rectangle(game->images.background, WINDOWS_WIDTH / 2 - 2,
		WINDOWS_HEIGHT / 2 - 2, 5, 5, false, 0x00ffffff);
}
