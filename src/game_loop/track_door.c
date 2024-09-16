/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:04:32 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/16 16:07:25 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	track_door(t_cub3d *game)
{
	if (game->door_time != -1)
	{
		if (my_system_time() - game->door_time > 2)
		{
			game->map.map[game->track_door[0]][game->track_door[1]] = '2';
			game->track_door[0] = -1;
			game->track_door[1] = -1;
			game->door_time = -1;
		}
	}
}
