/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:22:05 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/20 18:13:06 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
				game->player.pos.x = j * REC_WIDTH - (REC_WIDTH / 2);
				game->player.pos.y = i * REC_HEIGHT - (REC_HEIGHT / 2);
				if (game->map.map[i][j] == 'N')
					game->player.angle = 90;
				else if (game->map.map[i][j] == 'E')
					game->player.angle = 0;
				else if (game->map.map[i][j] == 'S')
					game->player.angle = 270;
				else if (game->map.map[i][j] == 'W')
					game->player.angle = 180;
				return ;
			}
	}
}
