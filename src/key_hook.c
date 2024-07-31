/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:19:00 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/31 20:12:34 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include <math.h>

void player_move(t_cub3d *game, bool key, double rad)
{
	t_vec2	new_pos;
	t_ray	ray;
	double	difference;

	if (key)
	{
		new_pos = game->player.pos;
		new_pos.x += cos(rad) * MOVE_SPEED;
		new_pos.y += sin(rad) * MOVE_SPEED;
		if (rad < 0)
			rad += 2 * M_PI;
		if (rad > 2 * M_PI)
			rad -= 2 * M_PI;
		ray = ray_throw(game, rad * (double)(180 / M_PI));
		if (ray.dis <= distance(game->player.pos, new_pos))
		{
			difference = 10;
			if (ray.dis < 10)
			{
				if (ray.v_h == 'v')
					difference = game->player.pos.x - ray.pos.x ;
				else
					difference = game->player.pos.y - ray.pos.y ;
			}
			if (ray.v_h == 'v')
				ray.pos.x += difference;
			else
				ray.pos.y += difference;
			game->player.pos = ray.pos;
		}
		else
			game->player.pos = new_pos;
		printf("x: %f - y: %f\n", game->player.pos.x, game->player.pos.y);
	}
}

void	update_player_status(t_cub3d *game)
{
	double	rad;

	rad = (game->player.angle) * (M_PI / 180.0);
	player_move(game, game->player.is_press_w, rad);
	player_move(game, game->player.is_press_d, rad + M_PI_2);
	player_move(game, game->player.is_press_s, rad - M_PI);
	player_move(game, game->player.is_press_a, rad - M_PI_2);
	if (game->player.is_press_p_rotation)
	{
		game->player.angle += 2.5;
		if (game->player.angle >= 360)
			game->player.angle -= 360;
	}
	if (game->player.is_press_n_rotation)
	{
		game->player.angle -= 2.5;
		if (game->player.angle < 0)
			game->player.angle += 360;
	}
	if (game->player.pos.y < 11.0)
		game->player.pos.y = 11.0;
	if (game->player.pos.y > game->map.height * REC_HEIGHT - 11.0)
		game->player.pos.y = game->map.height * REC_HEIGHT - 11.0;
	if (game->player.pos.x > game->map.width * REC_WIDTH - 11.0)
		game->player.pos.x = game->map.width * REC_WIDTH - 11.0;
	if (game->player.pos.x < 11.0)
		game->player.pos.x = 11.0;
}

int	key_down(int keycode, t_cub3d *game)
{
	if (keycode == KEY_LEFT)
		game->player.is_press_n_rotation = 1;
	if (keycode == KEY_RIGHT)
		game->player.is_press_p_rotation = 1;
	if (keycode == KEY_W)
		game->player.is_press_w = 1;
	if (keycode == KEY_A)
		game->player.is_press_a = 1;
	if (keycode == KEY_S)
		game->player.is_press_s = 1;
	if (keycode == KEY_D)
		game->player.is_press_d = 1;
	if (keycode == KEY_ESC)
		exit(1);
	return (0);
}

// tuşa bıraktığı anda t_cub3d structda bulunun değerleri false yapıyor. Bu sayede tuşa basılı tuttuğunu anlaşılıyor.
int	key_up(int keycode, t_cub3d *game)
{
	if (keycode == KEY_LEFT)
		game->player.is_press_n_rotation = 0;
	if (keycode == KEY_RIGHT)
		game->player.is_press_p_rotation = 0;
	if (keycode == KEY_W)
		game->player.is_press_w = 0;
	if (keycode == KEY_A)
		game->player.is_press_a = 0;
	if (keycode == KEY_S)
		game->player.is_press_s = 0;
	if (keycode == KEY_D)
		game->player.is_press_d = 0;
	return (0);
}

// ilk tıklamada bir kare seçer ikinci tıklamada ise 1. tıklamayla 2. tıklama arasına çizgi çeker.
/* int	mouse_click(int keycode, int x, int y, t_cub3d *game)
{
	if (keycode == 1)
	{
		if (!(x < 0 || y > MAP_HEIGHT * REC_HEIGHT || y < 0 || x > MAP_WIDTH * REC_WIDTH))
		{
			if (game->is_click == false)
			{
				game->is_click = true;
				game->click.y = y / REC_HEIGHT;
				game->click.x = x / REC_WIDTH;
				game->map.map[y / REC_HEIGHT][x / REC_WIDTH] = 0x0000FF00;
			}
			else
			{
				game->is_click = false;
				bresenham_line(game, game->click.x, game->click.y, x / REC_WIDTH, y / REC_HEIGHT, 0x00202020);
			}
		}
	}
	if (keycode == 2)
		if (!(x < 0 || y > MAP_HEIGHT * REC_HEIGHT || y < 0 || x > MAP_WIDTH * REC_WIDTH))
			game->map.map[y / REC_HEIGHT][x / REC_WIDTH] = 0x00252525;
	return (0);
} */
