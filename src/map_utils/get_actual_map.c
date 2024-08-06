/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_actual_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:15:17 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/06 18:19:19 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif

// check if xpm image paths are valid
// check if the files are empty
// turn xpm images to mlx images
// does that need malloc too??

// Copy map needs malloc checks
// Flood fill needs null checks

// COPY MAP
char	*empty_line(int width)
{
	char 	*map;

	map = ft_calloc(width + 1, sizeof(char));
	if (map == NULL)
		return (perror("cub3d"), NULL);
	ft_memset(map, ' ', width);
	map[width] = '\0';
	return (map);
}

static char **copy_map(t_tmp_map *tmp_map)
{
	char	**map;
	int		i;

	map = (char **)ft_calloc(tmp_map->height + 3, sizeof(char *));
	if (map == NULL)
		return (perror("cub3d"), free_tmp_map(tmp_map), exit(1), NULL);
	map[0] = empty_line(tmp_map->width + 2);
	map[tmp_map->height + 1] = empty_line(tmp_map->width + 2);
	map[tmp_map->height + 2] = NULL;
	i = -1;
	while (tmp_map->map[++i])
	{
		map[i + 1] = empty_line(tmp_map->width + 2);
		if (map[i + 1] == NULL)
			return (ft_strfree(map), free_tmp_map(tmp_map), exit(1), NULL);
		ft_memcpy(map[i + 1] + 1, tmp_map->map[i], ft_strlen(tmp_map->map[i]));
	}
	return (map);
}

// COPY MAP END

// PATH VALIDITY CHECKS
#include <fcntl.h>
#include <unistd.h>
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
// END OF PATH VALIDITY CHECKS

// DESTROYING IMAGES
void	delete_image(void *mlx, t_image *image)
{

}
// END OF DESTROYING IMAGES

void	initialize_images(char **paths)
{
	int	i;

	i =
}

// TEXTURE THINGS
t_image	*get_texture_image(char **paths)
{
	void	*mlx;
	t_image	*images;
	int		i;
	int		width;
	int		height;

	initialize_images();

	i = -1;
	while (paths[++i])
	{
		if (!the_path_is_valid(paths[i]))
			return (destroy_images(images), NULL);
		// needs a mlx pointer here!
		// images[i].image = mlx_xpm_file_to_image(mlx, paths[i], &width, &height);
	}
	return (images);
}

void	get_wall_textures(t_tmp_map *tmp_map, t_map *actual_map)
{
	actual_map->no = get_texture_image(tmp_map->no);
	actual_map->ea = get_texture_image(tmp_map->ea);
	actual_map->so = get_texture_image(tmp_map->so);
	actual_map->we = get_texture_image(tmp_map->we);
}
// TEXTURE THINGS END

t_map	get_actual_map(t_tmp_map *tmp_map)
{
	t_map	actual_map;
	char **map;

	map = copy_map(tmp_map);
	flood_fill(map, 0, 0);
	actual_map.map = map;
	get_wall_textures(tmp_map, &actual_map);
	return (actual_map);
}
