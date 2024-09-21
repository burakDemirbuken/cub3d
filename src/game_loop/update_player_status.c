/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:07:26 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/21 15:22:13 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minilibx/mlx.h"
#include "../../includes/libft/libft.h"
#include "../../includes/cub3d.h"
#include <math.h>

static inline t_vec2	collision(t_cub3d *game, t_vec2 pos)
{
	int		x;
	int		y;

	x = (int)(pos.x / REC_WIDTH);
	y = (int)(pos.y / REC_HEIGHT);
	if (game->player.pos.x < pos.x && get_offset(pos, 0.0, 'v') < 20
		&& ft_strchr("03", game->map.map[y][x + 1]) == 0)
		pos.x -= 20 - get_offset(pos, 0.0, 'v');
	else if (game->player.pos.x >= pos.x && get_offset(pos, M_PI, 'v') < 20
		&& ft_strchr("03", game->map.map[y][x - 1]) == 0)
		pos.x += 20 - get_offset(pos, M_PI, 'v');
	if (game->player.pos.y < pos.y && get_offset(pos, M_PI_2, 'h') < 20
		&& ft_strchr("03", game->map.map[y + 1][x]) == 0)
		pos.y -= 20 - get_offset(pos, M_PI_2, 'h');
	else if (game->player.pos.y >= pos.y
		&& get_offset(pos, MATH_3PI_2, 'h') < 20
		&& ft_strchr("03", game->map.map[y - 1][x]) == 0)
		pos.y += 20 - get_offset(pos, MATH_3PI_2, 'h');
	return (pos);
}

static void	player_move(t_cub3d *game, bool key, double rad)
{
	t_vec2	new_pos;
	t_ray	ray;

	if (!key)
		return ;
	new_pos = game->player.pos;
	if (rad <= 0)
		rad += MATH_2PI;
	if (rad >= MATH_2PI)
		rad -= MATH_2PI;
	if (fmod(rad, M_PI_2) == 0)
		rad += 0.0000042;
	ray.relat_angle = rad;
	ray_caster(game, &ray);
	if (ray.dis <= MOVE_SPEED)
		new_pos = ray.pos;
	else
	{
		new_pos.x += cos(rad) * MOVE_SPEED;
		new_pos.y += sin(rad) * MOVE_SPEED;
	}
	new_pos = collision(game, new_pos);
	if (ft_strchr("03", game->map.map[(int)(new_pos.y / REC_HEIGHT)]
		[(int)(new_pos.x / REC_HEIGHT)]) != 0)
		game->player.pos = new_pos;
}

static void	mouse_control(t_cub3d *game)
{
	int			x;
	int			y;

	if (game->mouse_control == true)
	{
		mlx_mouse_get_pos(game->win, &x, &y);
		if (20 < y && y < WINDOWS_HEIGHT)
		{
			game->player.angle += RAD_ANG * ((x - WINDOWS_WIDTH / 2) / 10);
			game->player.angle = fmod(game->player.angle, MATH_2PI);
			mlx_mouse_move(game->win, WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);
		}
	}
}

void	limit_player_in2map(t_cub3d *game)
{
	if (game->player.pos.y < 20.0)
		game->player.pos.y = 20.0;
	if (game->player.pos.y > game->map.height * REC_HEIGHT - 20.0)
		game->player.pos.y = game->map.height * REC_HEIGHT - 20.0;
	if (game->player.pos.x > game->map.width * REC_WIDTH - 20.0)
		game->player.pos.x = game->map.width * REC_WIDTH - 20.0;
	if (game->player.pos.x < 20.0)
		game->player.pos.x = 20.0;
}

void	update_player_status(t_cub3d *game)
{
	player_move(game, game->player.is_press_w, game->player.angle);
	player_move(game, game->player.is_press_d, game->player.angle + M_PI_2);
	player_move(game, game->player.is_press_s, game->player.angle - M_PI);
	player_move(game, game->player.is_press_a, game->player.angle - M_PI_2);
	if (game->player.is_press_p_rotation)
	{
		game->player.angle += RAD_ANG * 2.5;
		if (game->player.angle >= MATH_2PI)
			game->player.angle -= MATH_2PI;
	}
	if (game->player.is_press_n_rotation)
	{
		game->player.angle -= RAD_ANG * 2.5;
		if (game->player.angle < 0)
			game->player.angle += MATH_2PI;
	}
	limit_player_in2map(game);
	mouse_control(game);
	if (game->player.angle < 0)
		game->player.angle = MATH_2PI + game->player.angle;
}
