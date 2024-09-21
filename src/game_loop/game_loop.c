/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/21 14:22:15 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#ifdef __linux__
# include "../../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
# include "../../includes/minilibx/mlx.h"
#endif
#include "libft/libft.h"
#include <sys/time.h>
#include <unistd.h>

long double	my_system_time(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) == -1)
		return (my_system_time());
	return ((long double)time_value.tv_sec
		+ ((long double)time_value.tv_usec / 1000000.0));
}

int	game_loop(t_cub3d	*game)
{
	long double	start;
	char		a[12];

	update_player_status(game);
	paint_floor_ceiling(game);
	track_door(game);
	render_scene(game);
	mini_map(game);
	start = my_system_time();
	// sprintf needs to go?
	sprintf(a, "FPS: %.2Lf", 1 / (start - game->second));
	game->second = start;
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image,
		0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->images.minimap.image,
		25, 25);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, a);
	return (0);
}
