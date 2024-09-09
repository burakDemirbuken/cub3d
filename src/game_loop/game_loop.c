/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/09 11:08:45 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#ifdef __linux__
	#include "../../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../../includes/minilibx/mlx.h"
#endif
#include <math.h>

void	change_door_status(t_map *map, int x, int y)
{
	if (map->map[y][x] == '2')
		map->map[y][x] = '3';
	else if (map->map[y][x] == '3')
		map->map[y][x] = '2';
}

// Change this to the middle ray looking if the door is openable?
// Problem is, this way half of the rays will see the door and half of them not?
bool	access_to_door(t_cub3d *game, int *x, int *y)
{
	*x = game->player.pos.x / REC_WIDTH;
	*y = game->player.pos.y / REC_HEIGHT;
	if (game->player.angle > MATH_2PI - M_PI_4 && game->player.angle <= M_PI_4) // player looks north?
		(*y)++;
	// else if (game->player.angle > M_PI_4 && game->player.angle <= M_PI_2 + M_PI_4) // player looks east
		// (*x)--;
	// else if (game->player.angle > M_PI && game->player.angle <= MATH_3PI_2)
	// 	(*y)--;
	// else if (game->player.angle > MATH_3PI_2 && game->player.angle <= MATH_2PI)
	// 	(*x)++;
	if (*x >= 0 && *x < game->map.width && *y >= 0 && *y < game->map.height
		&& (game->map.map[*y][*x] == '2' || game->map.map[*y][*x] == '3'))
		return (true);
	else
		return (false);
}

void	update_door(t_cub3d *game)
{
	int	x;
	int	y;

	if (game->interact == true && access_to_door(game, &x, &y))
		change_door_status(&game->map, x, y);
	if (game->interact == true)
		game->interact = false;
}

int	game_loop(t_cub3d	*game)
{
	update_player_status(game);
	update_door(game);
	paint_floor_ceiling(game);
	render_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}
