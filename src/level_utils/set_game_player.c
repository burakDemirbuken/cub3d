/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:22:05 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/11 12:42:16 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

void	set_game_player(t_cub3d *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
				|| game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E')
			{
				game->player.pos.x = j * REC_WIDTH + (REC_WIDTH / 2);
				game->player.pos.y = i * REC_HEIGHT + (REC_HEIGHT / 2);
				if (game->map.map[i][j] == 'N')
					game->player.angle = M_PI_2;
				else if (game->map.map[i][j] == 'E')
					game->player.angle = MATH_2PI;
				else if (game->map.map[i][j] == 'S')
					game->player.angle = MATH_3PI_2;
				else if (game->map.map[i][j] == 'W')
					game->player.angle = M_PI;
				return ;
			}
	}
}
