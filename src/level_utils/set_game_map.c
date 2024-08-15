/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:17:40 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/15 13:56:39 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
// typedef t_cub3d
// typedef t_file
#include "../include/libft/libft.h"

static char	*empty_line(int width)
{
	char 	*map;

	map = ft_calloc(width + 1, sizeof(char));
	if (map == NULL)
		return (perror("cub3d"), NULL);
	ft_memset(map, ' ', width);
	map[width] = '\0';
	return (map);
}

static char	**copy_game_map(t_file *file)
{
	char	**map;
	int		i;

	map = (char **)ft_calloc(file->map_height + 3, sizeof(char *));
	if (!map)
		return (perror("cub3d"), free_file(file), exit(1), NULL);
	map[0] = empty_line(file->map_width + 2);
	map[file->map_height + 1] = empty_line(file->map_width + 2);
	map[file->map_height + 2] = NULL;
	i = -1;
	while (file->map[++i])
	{
		map[i + 1] = empty_line(file->map_width + 2);
		if (map[i + 1] == NULL)
			return (ft_strfree(map), free_file(file), exit(1), NULL);
		ft_memcpy(map[i + 1] + 1, file->map[i], ft_strlen(file->map[i]));
	}
	return (map);
}

static bool	flood_fill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || map[y] == NULL || map[y][x] == '\0')
		return (false);
	else if (map[y][x] == '1')
		return (false);
	else if (map[y][x] == ' ')
		map[y][x] = '1';
	else if (map[y][x] == '0')
		return (ft_putstr_fd("cub3d: Map must be surrounded by walls\n", 2),
			true);
	else
		return (ft_putstr_fd("cub3d: The map has undefined elements\n", 2),
			true);
	if (flood_fill(map, y, x - 1))
		return (true);
	if (flood_fill(map, y - 1, x))
		return (true);
	if (flood_fill(map, y, x + 1))
		return (true);
	return (flood_fill(map, y + 1, x));
}

void	set_game_map(t_cub3d *game, t_file *file)
{
	// this file needs funct. descriptions.
	game->map.map = copy_game_map(file);
	game->map.height = file->map_height;
	game->map.width = file->map_width;
	if (flood_fill(game->map.map, 0, 0))
	{
		ft_strfree(game->map.map);
		free_file(file);
		exit (1);
	}
}