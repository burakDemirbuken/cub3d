/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:38:57 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 15:51:58 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// typedef t_cub3d
// typedef t_file
#include "../../includes/libft/libft.h"
#include <stdlib.h>
#include "../../includes/minilibx/mlx.h"
#include <stdio.h>


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
	t_frame	*tmp;

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
	*frame = (t_frame *)malloc(sizeof(t_frame));
	if (!frame)
		return (perror(ERR_CUB3D), false);
	(*frame)->texture = import_image(mlx, path);
	if (!(*frame)->texture.image)
	{
		free(*frame);
		*frame = NULL;
		perror(ERR_CUB3D);
		return (false);
	}
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
	// Needs check for error messages
	if (!set_anim(&game->images.n, game->mlx, file->no))
		end_program(game, 1);
	else if (!set_anim(&game->images.s, game->mlx, file->so))
		end_program(game, 1);
	else if (!set_anim(&game->images.w, game->mlx, file->we))
		end_program(game, 1);
	else if (!set_anim(&game->images.e, game->mlx, file->ea))
		end_program(game, 1);
	game->images.door = import_image(game->mlx, "./textures/door.xpm");
	if (!game->images.door.image)
		end_program(game, 1);
}
