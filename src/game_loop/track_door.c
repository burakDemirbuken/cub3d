/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:04:32 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/23 12:03:00 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/*
 *	#define REC_HEIGHT 100
 *	#define REC_WIDTH 100
 *	#define DOOR '2'
 *	long double	my_system_time(void)
 */

void	track_door(t_cub3d *game)
{
	int	x;
	int	y;

	y = (game->player.pos.y / REC_HEIGHT);
	x = (game->player.pos.x / REC_WIDTH);
	if (game->door_time != -1
		&& !(y == game->track_door[0] && x == game->track_door[1]))
	{
		if (my_system_time() - game->door_time > 1)
		{
			game->map.map[game->track_door[0]][game->track_door[1]] = DOOR;
			game->track_door[0] = -1;
			game->track_door[1] = -1;
			game->door_time = -1;
		}
	}
}
