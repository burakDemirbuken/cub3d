/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/28 17:48:42 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#ifdef __linux__
	#include "../../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../../includes/minilibx/mlx.h"
#endif

int	game_loop(t_cub3d	*game)
{
	update_player_status(game);
	paint_floor_ceiling(game);
	render_scene(game);
	//draw_map(game);
	//mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}
