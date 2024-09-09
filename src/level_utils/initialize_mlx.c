/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:06:12 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/02 17:19:48 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/libft/libft.h"
#ifdef __linux__
# include "../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
# include "../includes/minilibx/mlx.h"
#endif

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
		return (false);
	game->shadow = false;
	game->mouse_control = false;
	game->interact = false;
	mlx_do_key_autorepeatoff(game->mlx);
	return (true);
}
