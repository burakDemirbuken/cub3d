/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:22:17 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/20 18:24:58 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// typedef t_cub3d

void	mini_map(t_cub3d *game)
{
	double	offset_x;
	double	offset_y;
	int		y;
	int		x;
	unsigned int color;

	y = 3;
	offset_x = fmod(game->player.pos.x, REC_WIDTH) / 4;
	offset_y = fmod(game->player.pos.y, REC_HEIGHT) / 4;
	while (y != 0)
	{
		x = 3;
		while (x != 0)
		{
			if (game->map.map[((int)(game->player.pos.y / REC_HEIGHT) + 3 ) - y][((int)(game->player.pos.x / REC_WIDTH) + 3) - x] == '1')
				color = 0x00345234;
			else
				color = 0x00983246;
			draw_rectangle(game->images.background, (y * 25) - offset_x, (x * 25) - offset_y ,25, 25, true, color);
			x--;
		}
		y--;
	}
/*

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT) - 1][(int)(game->player.pos.x / REC_WIDTH)] == '1')
		draw_rectangle(game->images.background, 50 - offset_x , 25 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 50 - offset_x , 25 - offset_y , 25, 25, false, 0x00983246);

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT) - 1][(int)(game->player.pos.x / REC_WIDTH) + 1] == '1')
		draw_rectangle(game->images.background, 75 - offset_x , 25 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 75 - offset_x , 25 - offset_y , 25, 25, false, 0x00983246);

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT)][(int)(game->player.pos.x / REC_WIDTH) - 1] == '1')
		draw_rectangle(game->images.background, 25 - offset_x , 50 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 25 - offset_x , 50 - offset_y , 25, 25, false, 0x00983246);

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT)][(int)(game->player.pos.x / REC_WIDTH)] == '1')
		draw_rectangle(game->images.background, 50 - offset_x , 50 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 50 - offset_x , 50 - offset_y , 25, 25, false, 0x00983246);

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT)][(int)(game->player.pos.x / REC_WIDTH) + 1] == '1')
		draw_rectangle(game->images.background, 75 - offset_x , 50 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 75 - offset_x , 50 - offset_y , 25, 25, false, 0x00983246);

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT) + 1][(int)(game->player.pos.x / REC_WIDTH) - 1] == '1')
		draw_rectangle(game->images.background, 25 - offset_x , 75 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 25 - offset_x , 75 - offset_y , 25, 25, false, 0x00983246);

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT) + 1][(int)(game->player.pos.x / REC_WIDTH)] == '1')
		draw_rectangle(game->images.background, 50 - offset_x , 75 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 50 - offset_x , 75 - offset_y , 25, 25, false, 0x00983246);

	if (game->map.map[(int)(game->player.pos.y / REC_HEIGHT) + 1][(int)(game->player.pos.x / REC_WIDTH) + 1] == '1')
		draw_rectangle(game->images.background, 75 - offset_x , 75 - offset_y , 25, 25, false, 0x00345234);
	else
		draw_rectangle(game->images.background, 75 - offset_x , 75 - offset_y , 25, 25, false, 0x00983246);

 */
	draw_rectangle(game->images.background, 25 + 25 - 1 , 25 + 25 - 1 , 3, 3, false, 0x00FF0000);
}
