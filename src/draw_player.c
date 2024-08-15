/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:10:02 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/15 12:56:04 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
#include <stdlib.h>

void	draw_player(t_cub3d *game)
{
	draw_rectangle(game->images.background, game->player.pos.x / 5 - 2 + 25,
		game->player.pos.y / 5 - 2 + 25, 5, 5, false, 0x00FF0000);
}
