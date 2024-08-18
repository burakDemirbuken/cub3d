/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/18 15:44:52 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <math.h>
#include <stdio.h>

t_ray	ray_throw(t_cub3d *game, double angle)
{
	double	horizontal_ray_distance;
	double	vertical_ray_distance;
	t_vec2	horizontal_ray_pos;
	t_vec2	vertical_ray_pos;
	t_ray	ret;
	double	tan_a;
	double	rad;

	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	if (fmod(angle, 45) == 0)
		angle += 0.000042;
	ret.angle = angle;
	rad = ret.angle * (RAD_CONVERT);
	tan_a = tan(rad);
	horizontal_ray_pos = horizontal_ray_calculator(game, rad, tan_a);
	vertical_ray_pos = vertical_ray_calculator(game, rad, tan_a);
	horizontal_ray_distance = distance(game->player.pos, horizontal_ray_pos);
	vertical_ray_distance = distance(game->player.pos, vertical_ray_pos);
	if (horizontal_ray_distance > vertical_ray_distance)
	{
		ret.pos = vertical_ray_pos;
		ret.dis = vertical_ray_distance;
		ret.v_h = 'v';
	}
	else
	{
		ret.pos = horizontal_ray_pos;
		ret.dis = horizontal_ray_distance;
		ret.v_h = 'h';
	}
	return (ret);
}

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

int	game_loop(t_cub3d	*game)
{
	update_player_status(game);
	display(game);
	//draw_map(game);
	mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}
