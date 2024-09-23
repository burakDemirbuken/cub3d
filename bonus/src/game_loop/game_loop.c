/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/23 18:03:23 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
/*
 *	typedef struct s_cub3d t_cub3d
 *	void	update_player_status(t_cub3d *game)
 *	void	paint_floor_ceiling(t_cub3d *game)
 *	void	track_door(t_cub3d *game)
 *	void	render_scene(t_cub3d *game)
 *	void	mini_map(t_cub3d *game)
 */
#include "minilibx/mlx.h"
/*
 *	int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr,
 									void *img_ptr, int x, int y)
 *	int	mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y,
 									int color, char *string)
 */
#include "libft/libft.h"
/*
 *	size_t ft_strlcpy(char *dest, const char *src, size_t dstsize)
 */
#include <sys/time.h>
/*
 *	struct timeval
 *	int gettimeofday(struct timeval *__restrict__, void *__restrict__)
 */

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

void	get_fps(t_cub3d *game, char *fps)
{
	long double	start;
	int			fps_value;

	start = my_system_time();
	ft_strlcpy(fps, "FPS: ", 6);
	fps_value = (int)(1 / (start - game->second));
	fps[5] = (fps_value / 10) + '0';
	fps[6] = (fps_value % 10) + '0';
	fps[7] = 0;
	game->second = start;
}

int	game_loop(t_cub3d	*game)
{
	char	fps[8];

	update_player_status(game);
	paint_floor_ceiling(game);
	track_door(game);
	render_scene(game);
	mini_map(game);
	get_fps(game, fps);
	next_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image,
		0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->images.minimap.image,
		25, 25);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, fps);
	return (0);
}
