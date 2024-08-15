/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_animate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:37:16 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/15 16:22:22 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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

t_animations create_animate(t_cub3d *game, char **paths)
{
	t_animations	ret;
	t_frame			*frame;
	int				i;

	ret.frame = (t_frame *)malloc(sizeof(t_frame));
	if (!ret.frame)
		exit(1); //	free
	ret.frame->texture = import_image(game->mlx, paths[0]);
	if (!ret.frame->texture.image)
		exit(1); //	free
	frame = ret.frame;
	i = 1;
	while (paths[i])
	{
		frame->next = (t_frame *)malloc(sizeof(t_frame));
		if (!frame->next)
			exit(1); //	free
		frame->next->texture = import_image(game->mlx, paths[i]);
		if (!frame->next->texture.image)
			exit(1); //	free
		frame->next->prev = frame;
		frame = frame->next;
		i++;
	}
	ret.frame->prev = frame;
	frame->next = ret.frame;
	ret.frame_count = i;
	return (ret);
}
