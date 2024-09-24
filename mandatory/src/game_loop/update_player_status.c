/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:07:26 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/24 10:29:11 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
/*
 *	char *ft_strchr(const char *s, int c)
 */
#include "cub3d.h"
/*
 *	#include <stdbool.h>
 	-	#define true 1
 *	typedef struct s_cub3d t_cub3d
 *	typedef struct s_vec2 t_vec2
 *	typedef struct s_ray t_ray
 *	#define MATH_2PI	6.28318530717958647692528676655900576
 *	#define MATH_3PI_2	4.71238898038468985769396507491925432
 *	#define RAD_ANG		0.017453292519943295474371680597869271
 *	#define WINDOWS_HEIGHT	1080
 *	#define WINDOWS_WIDTH	1920
 *	#define MOVE_SPEED	6
 *	#define REC_WIDTH	100
 *	#define REC_HEIGHT	100
 *	double	get_offset(t_vec2 p_pos, double rad, char v_h)
 */
#include <math.h>
/*
 *	#define M_PI 3.14159265358979323846264338327950288
 *	#define M_PI_2 1.57079632679489661923132169163975144
 */

static t_vec2	collision(t_cub3d *game, t_vec2 pos)
{
	// collison bozuk
	int		x;
	int		y;

	x = (int)(pos.x / REC_WIDTH);
	y = (int)(pos.y / REC_HEIGHT);
	if (game->player.pos.x < pos.x && get_offset(pos, 0.0, 'v') < 20
		&& ft_strchr("0", game->map.map[y][x + 1]) == 0)
		pos.x -= 20 - get_offset(pos, 0.0, 'v');
	else if (game->player.pos.x >= pos.x && get_offset(pos, M_PI, 'v') < 20
		&& ft_strchr("0", game->map.map[y][x - 1]) == 0)
		pos.x += 20 - get_offset(pos, M_PI, 'v');
	if (game->player.pos.y < pos.y && get_offset(pos, M_PI_2, 'h') < 20
		&& ft_strchr("0", game->map.map[y + 1][x]) == 0)
		pos.y -= 20 - get_offset(pos, M_PI_2, 'h');
	else if (game->player.pos.y >= pos.y
		&& get_offset(pos, MATH_3PI_2, 'h') < 20
		&& ft_strchr("0", game->map.map[y - 1][x]) == 0)
		pos.y += 20 - get_offset(pos, MATH_3PI_2, 'h');
	return (pos);
}

static void	player_move(t_cub3d *game, bool key, double rad)
{
	t_vec2	new_pos;

	if (!key)
		return ;
	new_pos = game->player.pos;
	if (rad <= 0)
		rad += MATH_2PI;
	if (rad >= MATH_2PI)
		rad -= MATH_2PI;
	new_pos.x += cos(rad) * MOVE_SPEED;
	new_pos.y += sin(rad) * MOVE_SPEED;
	new_pos = collision(game, new_pos);
	game->player.pos = new_pos;
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
	if (game->player.angle < 0)
		game->player.angle = MATH_2PI + game->player.angle;
}
