/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:38:57 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/16 12:13:41 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
// typedef t_cub3d
// typedef t_file
#include "libft/libft.h"
#include <stdlib.h>
#ifdef __linux__
# include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
# include "../include/minilibx/mlx.h"
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

void	destroy_anim(void *mlx, t_animations *anim)
{
	t_frame	*tmp;

	anim->frame->prev->next = NULL;
	while (anim->frame)
	{
		mlx_destroy_image(mlx, anim->frame->texture.image);
		tmp = anim->frame->next;
		free(anim->frame);
		anim->frame = tmp;
	}
}

static bool	create_frame(t_frame *frame, void *mlx, char *path)
{
	if (!the_path_is_valid(path))
		return (false);
	frame = (t_frame *)malloc(sizeof(t_frame));
	if (!frame)
		return (perror("cub3d"), false);
	frame->texture = import_image(mlx, path);
	if (!frame->texture.image)
		return (perror("cub3d"), false);
}

static bool	set_anim(t_animations *anim, void *mlx, char **paths)
{
	t_frame	*frame;
	int		i;

	if (!create_frame(anim->frame, mlx, paths[0]))
		return (false);
	frame = anim->frame;
	i = 0;
	while (paths[++i])
	{
		if (!create_frame(frame->next, mlx, paths[i]))
			return (false);
		frame->next->prev = frame;
		frame = frame->next;
	}
	anim->frame->prev = frame;
	frame->next = anim->frame;
	anim->frame_count = i;
	return (true);
}

void	set_game_sprites(t_cub3d *game, t_file *file)
{
	// this file needs function descriptions
	// also needs a check for error messages
	if (!set_anim(&game->images.N, game->mlx, file->no))
		end_program(game, 1);
	else if (!set_anim(&game->images.S, game->mlx, file->so))
		end_program(game, 1);
	else if (!set_anim(&game->images.W, game->mlx, file->we))
		end_program(game, 1);
	else if (!set_anim(&game->images.E, game->mlx, file->ea))
		end_program(game, 1);
}
