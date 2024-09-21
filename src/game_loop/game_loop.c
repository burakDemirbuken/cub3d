/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/21 15:36:21 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/minilibx/mlx.h"
#include "libft/libft.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long double	my_system_time(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) == -1)
		return (my_system_time());
	return ((long double)time_value.tv_sec
		+ ((long double)time_value.tv_usec / 1000000.0));
}
void	next_frame(t_cub3d *game)
{
	if (!(my_system_time() - game->frame_second > 0.1))
		return ;
	game->images.e = game->images.e->next;
	game->images.w = game->images.w->next;
	game->images.n = game->images.n->next;
	game->images.s = game->images.s->next;
	game->frame_second = my_system_time();
}

int	game_loop(t_cub3d	*game)
{
	long double	start;
	char		fps[12];

	update_player_status(game);
	paint_floor_ceiling(game);
	track_door(game);
	render_scene(game);
	mini_map(game);
	start = my_system_time();
	// sprintf needs to go?
	sprintf(fps, "FPS: %.2Lf", 1 / (start - game->second));
	game->second = start;
	next_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image,
		0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->images.minimap.image,
		25, 25);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, fps);
	return (0);
}
