/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:38:57 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/15 17:18:54 by bkorkut          ###   ########.fr       */
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
#include <fcntl.h>

bool	the_path_is_valid(char *path)
{
	int		fd;
	char	line[10];
	int		bytes;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror("cub3d"), false);
	bytes = read(fd, line, 9);
	close(fd);
	if (bytes <= 0)
		return (perror("cub3d"), false);
	if (ft_strncmp(line, "/* XPM */", 9))
		return (perror("cub3d"), false);
	return (true);
}

t_image	import_image(void *mlx, char *path)
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

bool	create_anim(t_animations *anim, void *mlx, char **paths)
{
	t_frame	*frame;
	int		i;

	anim->frame = (t_frame *)malloc(sizeof(t_frame));
	if (!anim->frame)
		return (perror("cub3d"), false);
	anim->frame->texture = import_image(mlx, paths[0]);
	if (!anim->frame->texture.image)
		return (perror("cub3d"), false);
	frame = anim->frame;
	i = 1;
	while (paths[i])
	{
		frame->next = (t_frame *)malloc(sizeof(t_frame));
		if (!frame->next)
			return (perror("cub3d"), false);
		frame->next->texture = import_image(mlx, paths[i]);
		if (!frame->next->texture.image)
			return (perror("cub3d"), false);
		frame->next->prev = frame;
		frame = frame->next;
		i++;
	}
	anim->frame->prev = frame;
	frame->next = anim->frame;
	anim->frame_count = i;
	return (true);
}

void	set_game_sprites(t_cub3d *game, t_file *file)
{
	if (!create_anim(&game->images.N, game->mlx, file->no))
		end_program();
	else if (!create_anim(&game->images.S, game->mlx, file->so))
		end_program();
	else if (!create_anim(&game->images.W, game->mlx, file->we))
		end_program();
	else if (!create_anim(&game->images.E, game->mlx, file->ea))
		end_program();
}