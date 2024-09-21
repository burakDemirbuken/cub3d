/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:22:17 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 14:35:06 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/libft/libft.h"
#include <math.h>

void	draw_rectangle(t_image img, t_int_vec2 pos, t_int_vec2 dimensions,
						int color)
{
	int		i_h;
	int		i_w;

	i_h = 0;
	while (i_h < dimensions.y)
	{
		i_w = 0;
		while (i_w < dimensions.x)
		{
			if (i_w + pos.x < 1 || i_w + pos.x > WINDOWS_WIDTH - 1
				|| i_h + pos.y < 0 || i_h + pos.y > WINDOWS_HEIGHT - 1)
			{
				i_w++;
				continue ;
			}
			if (color != 0x10000000 && (i_w == dimensions.x - 1 || i_w == 0
					|| i_h == dimensions.y - 1 || i_h == 0))
				put_pixel_to_image(img, pos.x + i_w, pos.y + i_h, 0x10303030);
			else
				put_pixel_to_image(img, pos.x + i_w, pos.y + i_h, color);
			i_w++;
		}
		i_h++;
	}
}

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

void	place_rectangle(t_cub3d *game, t_int_vec2 pos, t_vec2 offset,
						t_int_vec2 dimensions)
{
	unsigned int	color;

	if (0 <= pos.x && pos.x < game->map.width && 0 <= pos.y
		&& pos.y < game->map.height
		&& ft_strchr("0123", game->map.map[pos.y][pos.x]) != NULL)
	{
		if (game->map.map[pos.y][pos.x] == '1')
			color = 0x10743224;
		else if (game->map.map[pos.y][pos.x] == '2')
			color = 0x10435231;
		else if (game->map.map[pos.y][pos.x] == '3')
			color = 0x10204693;
		else
			color = 0x10236412;
		draw_rectangle(game->images.minimap, (t_int_vec2)
		{(dimensions.y * 25) - offset.x, (dimensions.x * 25) - offset.y},
			(t_int_vec2){25, 25}, color);
	}
	else
		draw_rectangle(game->images.minimap, (t_int_vec2)
		{(dimensions.y * 25) - offset.x, (dimensions.x * 25) - offset.y},
			(t_int_vec2){25, 25}, 0x10000000);
}

void	mini_map(t_cub3d *game)
{
	t_vec2			offset;
	t_int_vec2		dimensions;
	t_int_vec2		pos;

	dimensions.y = 0;
	offset.x = fmod(game->player.pos.y, REC_WIDTH) / 4;
	offset.y = fmod(game->player.pos.x, REC_HEIGHT) / 4;
	while (dimensions.y < 11)
	{
		dimensions.x = 0;
		pos.y = ((int)(game->player.pos.y / REC_HEIGHT)) + dimensions.y - 5;
		while (dimensions.x < 11)
		{
			pos.x = ((int)(game->player.pos.x / REC_WIDTH)) + dimensions.x - 5;
			place_rectangle(game, pos, offset, dimensions);
			dimensions.x++;
		}
		dimensions.y++;
	}
	draw_circle(game, 125, 125, 125);
	draw_rectangle(game->images.minimap,
		(t_int_vec2){(game->images.minimap.width / 2) - 2,
		(game->images.minimap.height / 2) - 2}, (t_int_vec2){5, 5}, 0x10FF0000);
	draw_rectangle(game->images.background, (t_int_vec2){WINDOWS_WIDTH / 2 - 2,
		WINDOWS_HEIGHT / 2 - 2}, (t_int_vec2){5, 5}, 0x10ffffff);
}
