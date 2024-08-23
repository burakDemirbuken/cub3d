/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:38:57 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/23 14:58:28 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// typedef t_cub3d
// typedef t_file
#include "../../includes/libft/libft.h"
#include <stdlib.h>
#ifdef __linux__
# include "../../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
# include "../../includes/minilibx/mlx.h"
#endif

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

void	destroy_anim(void *mlx, t_frame *anim)
{
	t_frame *tmp;

	anim->prev->next = NULL;
	while (anim)
	{
		mlx_destroy_image(mlx, anim->texture.image);
		tmp = anim->next;
		free(anim);
		anim = tmp;
	}
}

static bool	create_frame(t_frame **frame, void *mlx, char *path)
{
	if (!the_path_is_valid(path))
		return (false);
	*frame = (t_frame *)malloc(sizeof(t_frame));
	if (!frame)
		return (perror(ERR_CUB3D), false);
	(*frame)->texture = import_image(mlx, path);
	if (!(*frame)->texture.image)
		return (perror(ERR_CUB3D), false);
	return (true);
}

static bool	set_anim(t_frame **anim, void *mlx, char **paths)
{
	t_frame	*frame;
	int		i;

	if (!create_frame(anim, mlx, paths[0]))
		return (false);
	frame = *anim;
	i = 0;
	while (paths[++i])
	{
		if (!create_frame(&frame->next, mlx, paths[i]))
			return (false);
		frame->next->prev = frame;
		frame = frame->next;
	}
	(*anim)->prev = frame;
	frame->next = (*anim);
	return (true);
}

void	set_game_sprites(t_cub3d *game, t_file *file)
{
	// this file needs function descriptions
	// also needs a check for error messages
	char *door[14];
	char *door_wall = "./textures/doors_inner_wall.xpm";
	door[0] = "./textures/door_00.xpm";
	door[1] = "./textures/door_01.xpm";
	door[2] = "./textures/door_02.xpm";
	door[3] = "./textures/door_03.xpm";
	door[4] = "./textures/door_04.xpm";
	door[5] = "./textures/door_05.xpm";
	door[6] = "./textures/door_06.xpm";
	door[7] = "./textures/door_07.xpm";
	door[8] = "./textures/door_08.xpm";
	door[9] = "./textures/door_09.xpm";
	door[10] = "./textures/door_10.xpm";
	door[11] = "./textures/door_11.xpm";
	door[12] = "./textures/door_12.xpm";
	door[13] = NULL;

	if (!set_anim(&game->images.n, game->mlx, file->no))
		end_program(game, 1);
	else if (!set_anim(&game->images.s, game->mlx, file->so))
		end_program(game, 1);
	else if (!set_anim(&game->images.w, game->mlx, file->we))
		end_program(game, 1);
	else if (!set_anim(&game->images.e, game->mlx, file->ea))
		end_program(game, 1);
	else if (!set_anim(&game->images.door, game->mlx, door))
		end_program(game, 1);
	game->images.door_inner_wall = import_image(game->mlx, door_wall);
	if (!game->images.door_inner_wall.image)
		end_program(game, 1);
}
