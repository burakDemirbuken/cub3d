/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_actual_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:15:17 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/05 17:41:17 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"

// check if xpm image paths are valid
// check if the files are empty
// turn xpm images to mlx images
// does that need malloc too??

// Copy map for flood fill
// Flood fill

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

t_map	get_actual_map(t_tmp_map *tmp_map)
{
	t_map	actual_map;
	char **map;

	map = copy_map(tmp_map);
	print_map(map);
	flood_fill(map, 0, 0);
	print_map(map);
	actual_map.map = map;
	return (actual_map);
}
