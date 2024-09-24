/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:38:57 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/24 10:27:47 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
 *	typedef struct s_image t_image
 *	typedef struct s_frame t_frame
 *	ERR_CUB3D "cub3D"
 *	void	free_file(t_file *file)
 *	bool	the_path_is_valid(char *path)
 *	void	end_program(t_cub3d *game, int e)
 *	#include <stdbool.h>
 	-	#define bool _Bool
 	-	#define true 1
 	-	#define false 0

 */
#include "libft/libft.h"
/*
 *	#include <stdlib.h>
	-	void	free(void *)
	-	void	*malloc(size_t __size)

 */
#include "minilibx/mlx.h"
/*
 *	char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
 									int *size_line, int *endian)
 *	void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width,
 									int *height)
 *	int		mlx_destroy_image(void *mlx_ptr, void *img_ptr)
 */
#include <unistd.h>
/*
 *	STDERR_FILENO 2
 */

static t_image	import_image(void *mlx, char *path)
{
	t_image	img;

	ft_memset(&img, 0, sizeof(t_image));
	img.image = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.image)
		return (img);
	img.data = mlx_get_data_addr(img.image, &img.bits_per_pixel,
			&img.line_lenght, &img.endian);
	return (img);
}

void	set_game_sprites(t_cub3d *game, t_file *file)
{
	game->images.n = import_image(game->mlx, file->no);
	if (!game->images.n.image)
		return (ft_putstr_fd(ERR_CRIMG, STDERR_FILENO),
			free_file(file), end_program(game, 1));
	game->images.s = import_image(game->mlx, file->so);
	if (!game->images.s.image)
		return (ft_putstr_fd(ERR_CRIMG, STDERR_FILENO),
			free_file(file), end_program(game, 1));
	game->images.w = import_image(game->mlx, file->we);
	if (!game->images.w.image)
		return (ft_putstr_fd(ERR_CRIMG, STDERR_FILENO),
			free_file(file), end_program(game, 1));
	game->images.e = import_image(game->mlx, file->ea);
	if (!game->images.e.image)
		return (ft_putstr_fd(ERR_CRIMG, STDERR_FILENO),
			free_file(file), end_program(game, 1));
	game->images.door = import_image(game->mlx, "./textures/door.xpm");
	if (!game->images.door.image)
		return (ft_putstr_fd(ERR_CRIMG, STDERR_FILENO),
			free_file(file), end_program(game, 1));
}
