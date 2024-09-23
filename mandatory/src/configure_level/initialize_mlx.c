/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:06:12 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/23 18:14:21 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
 *	# include <stdbool.h>
	-
 *	typedef struct s_image t_image
 *
 */
#include "libft/libft.h"
/*
 *	void	*ft_memset(void *b, int c, size_t len)
 */
#include "minilibx/mlx.h"
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
	game->shadow = false;
	mlx_do_key_autorepeatoff(game->mlx);
	return (true);
}
