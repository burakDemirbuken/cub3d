/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:07:26 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/28 15:48:18 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
	#include "../../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../../includes/minilibx/mlx.h"
#endif
/*
 *	int mlx_mouse_get_pos(void *win_ptr, int *x, int *y)
 *	int mlx_mouse_hide()
 *	int mlx_mouse_show()
 *	int mlx_mouse_move(void *win_ptr, int x, int y)
 */
#include "../../includes/cub3d.h"
/*
 *	t_ray ray_throw(t_cub3d *game, double angle)
 *	typedef struct s_cub3d t_cub3d
 *	RAD_ANG	0.0174532925199432954743716805978692718781530857086181640625
 *	REC_HEIGHT	100
 *	REC_WIDTH	100
 *	WINDOWS_HEIGHT	1080
 *	WINDOWS_WIDTH	1920
 */
#include <math.h>
/*
 *	double cos(double)
 *	double cos(double)
 *	double fabs(double)
 */

static void	player_move(t_cub3d *game, bool key, double rad)
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
			rad += MATH_2PI;
		if (rad > MATH_2PI)
			rad -= MATH_2PI;
		ray.relat_angle = rad;
		ray_throw(game, &ray);
		if (ray.dis <= MOVE_SPEED)
		{
			difference = 10;
			if (ray.dis < 10 && ray.v_h == 'v')
				difference = fabs(game->player.pos.x - ray.pos.x);
			else if (ray.dis < 10)
				difference = fabs(game->player.pos.y - ray.pos.y);
			if (ray.v_h == 'v' && game->player.pos.x < ray.pos.x)
				ray.pos.x -= difference;
			else if (ray.v_h == 'v')
				ray.pos.x += difference;
			if (ray.v_h != 'v' && game->player.pos.y < ray.pos.y)
				ray.pos.y -= difference;
			else if (ray.v_h != 'v')
				ray.pos.y += difference;
			game->player.pos = ray.pos;
		}
		else
			game->player.pos = new_pos;
	}
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
			mlx_mouse_move(game->win, WINDOWS_WIDTH / 2, y);
		}
	}
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
	if (game->player.pos.y < 11.0)
		game->player.pos.y = 11.0;
	if (game->player.pos.y > game->map.height * REC_HEIGHT - 11.0)
		game->player.pos.y = game->map.height * REC_HEIGHT - 11.0;
	if (game->player.pos.x > game->map.width * REC_WIDTH - 11.0)
		game->player.pos.x = game->map.width * REC_WIDTH - 11.0;
	if (game->player.pos.x < 11.0)
		game->player.pos.x = 11.0;
	mouse_control(game);
}
