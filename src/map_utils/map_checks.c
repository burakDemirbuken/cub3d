/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:07:31 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/26 16:28:56 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 6 elements come before the map
// All six elements need to be peresent

#include "../../include/cub3d.h"

int get_maplen(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

// flood fill algorithm does tha deed!

// map check is not complete!
static void	map_checker(char **map, int y, int x, int *flag)
{
	char	c;

	if (map[y][x] == '1')
		return ;
	else if (y == 0 || y == ft_maplen(map) || x == 0 || x == ft_strlen(map[y]))
	{
		ft_putstr_fd("Map must be surrounded by walls\n", 2);
		*flag = 1;
	}
	else if (map[y][x] != '1' && map[y][x] != '0')
		return (ft_putstr_fd("The map has undefined elements\n", 2), *flag = 1);
	c = map[y][x];
	map[y][x] = '1';
	path_finder(map, y, x - 1);
	path_finder(map, y - 1, x);
	path_finder(map, y, x + 1);
	path_finder(map, y + 1, x);
	map[y][x] = c;
}

void	map_checks(char **map)
{
	int		i[2];
	int		start[2];
	char	c;
	int		flag;

	i[0] = -1;
	start[0] = -1;
	while (map[++i[0]] && *start == -1)
	{
		i[1] = -1;
		while(map[i[0]][++i[1]] && *start == -1)
		{
			if (map[i[0]][i[1]] == 'N' || map[i[0]][i[1]] == 'S'
				|| map[i[0]][i[1]] == 'W' || map[i[0]][i[1]] == 'E')
			{
				start[0] = i[0];
				start[1] = i[1];
				c = map[i[0]][i[1]];
				map[i[0]][i[1]] = '0';
			}
		}
	}
	flag = 0;
	map_checker(map, start[0], start[1], &flag);
	map[start[0]][start[1]] = c;
}
