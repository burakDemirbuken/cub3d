/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/23 18:09:29 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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

int	game_loop(t_cub3d	*game)
{
	char	fps[8];

	update_player_status(game);
	paint_floor_ceiling(game);
	render_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image,
		0, 0);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, fps);
	return (0);
}
