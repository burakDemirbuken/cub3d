/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:06:12 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 17:24:24 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/*
 *	# include <stdbool.h>
	- 
 *	typedef struct s_image t_image
 *
 */
#include "../../includes/libft/libft.h"
/*
 *	void	*ft_memset(void *b, int c, size_t len)
 */
#include "../includes/minilibx/mlx.h"
/*
 *	void	*mlx_init()
 *	int		mlx_do_key_autorepeatoff(void *mlx_ptr)
 *	void	*mlx_new_image(void *mlx_ptr, int width, int height)
 *	int		mlx_destroy_window(void *mlx_ptr, void *win_ptr)
 *	char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
 				int *size_line, int *endian)
 */

static t_image	create_new_image(void *mlx, int width, int height)
{
	t_image	img;

	ft_memset(&img, 0, sizeof(t_image));
	img.image = mlx_new_image(mlx, width, height);
	if (!img.image)
		return (img);
	img.data = mlx_get_data_addr(img.image, &img.bits_per_pixel,
			&img.line_lenght, &img.endian);
	img.height = height;
	img.width = width;
	return (img);
}

bool	initialize_mlx(t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->win = mlx_new_window(game->mlx,
			WINDOWS_WIDTH, WINDOWS_HEIGHT, ERR_CUB3D);
	if (!game->win)
		return (false);
	game->images.background = create_new_image(game->mlx, WINDOWS_WIDTH,
			WINDOWS_HEIGHT);
	if (!game->images.background.image)
		return (mlx_destroy_window(game->mlx, game->win), false);
	game->images.minimap = create_new_image(game->mlx, 250, 250);
	if (!game->images.minimap.image)
		return (mlx_destroy_image(game->mlx, game->images.background.image),
			mlx_destroy_window(game->mlx, game->win), false);
	game->shadow = false;
	game->mouse_control = false;
	game->track_door[0] = -1;
	game->track_door[1] = -1;
	game->door_time = -1;
	mlx_do_key_autorepeatoff(game->mlx);
	return (true);
}
