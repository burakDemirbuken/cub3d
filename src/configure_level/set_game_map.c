/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:17:40 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 17:42:24 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// typedef t_cub3d
// typedef t_file
// ERR_CUB3D "cub3D"
// free_file(t_file *file)
#include "../includes/libft/libft.h"
// ft_calloc(size_t count, size_t size)
// ft_strfree(char **a)
// ft_memcpy(void *dst, const void *src, size_t n)
// ft_putstr_fd(char *s, int fd)
// ft_strlen(const char *s)
// <stdlib.h>
// |-->	exit(int)
#include <unistd.h>
// STDERR_FILENO
#include <stdio.h>
// perror(const char *)

static char	*empty_line(int width)
{
	char	*map;

	map = ft_calloc(width + 1, sizeof(char));
	if (map == NULL)
		return (perror(ERR_CUB3D), NULL);
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
		return (perror(ERR_CUB3D), free_file(file), exit(1), NULL);
	map[0] = empty_line(file->map_width + 2);
	if (map[0] == NULL)
		return (free(map), free_file(file), exit(1), NULL);
	i = -1;
	while (file->map[++i])
	{
		map[i + 1] = empty_line(file->map_width + 2);
		if (map[i + 1] == NULL)
			return (ft_strfree(map), free_file(file), exit(1), NULL);
		ft_memcpy(map[i + 1] + 1, file->map[i], ft_strlen(file->map[i]));
	}
	map[file->map_height + 1] = empty_line(file->map_width + 2);
	if (map[file->map_height + 1] == NULL)
		return (ft_strfree(map), free_file(file), exit(1), NULL);
	map[file->map_height + 2] = NULL;
	return (map);
}

static bool	flood_fill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || map[y] == NULL || map[y][x] == '\0')
		return (false);
	else if (map[y][x] == '1' || map[y][x] == 'M')
		return (false);
	else if (map[y][x] == ' ')
		map[y][x] = 'M';
	else if (map[y][x] == '0' || map[y][x] == DOOR)
		return (ft_putstr_fd(ERR_NOWALL, STDERR_FILENO), true);
	else
		return (ft_putstr_fd(ERR_MUNDEF, STDERR_FILENO), true);
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
	int	i;
	int	j;

	game->map.map = copy_game_map(file);
	game->map.height = file->map_height + 2;
	game->map.width = file->map_width + 2;
	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == ' ' && flood_fill(game->map.map, i, j))
			{
				ft_strfree(game->map.map);
				free_file(file);
				exit (1);
			}
			j++;
		}
		i++;
	}
}
