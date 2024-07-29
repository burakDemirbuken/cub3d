/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:07:31 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/29 18:15:46 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 6 elements come before the map
// All six elements need to be peresent

#include "../../include/cub3d.h"
#include "../../include/libft/libft.h"

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
static void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == '1')
		return ;
	else if (map[y][x] == ' ')
		map[y][x] = '#';
	else
		ft_putstr_fd("Map must be surrounded by walls\n", 2);
	flood_fill(map, y, x - 1);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y + 1, x);
}

void	print_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		ft_putstr_fd(map[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	map_checks(char **map)
{
	char	**new_map;
	int		arrlen;
	int		strlen;

	print_map(map);
	arrlen = get_maplen(map);
	//trim_nl();
	new_map = ft_calloc(arrlen + 2, sizeof(char *));
	strlen = ft_strlen(map[0]);
	new_map[0] = ft_calloc(strlen + 2, sizeof(char));
	new_map[0][strlen + 2] = '\0';
	while (strlen--)
		new_map[0][strlen] = ' ';
	arrlen = 0;
	while (map[arrlen])
	{
		new_map[arrlen + 1] = ft_strjoin(" ", map[arrlen]);
		arrlen++;
	}
	strlen = ft_strlen(map[arrlen]);
	new_map[arrlen + 1] = ft_calloc(strlen + 2, sizeof(char));
	new_map[arrlen + 1][strlen + 2] = '\0';
	while (strlen--)
		new_map[arrlen + 1][strlen] = ' ';
	flood_fill(new_map, 0, 0);
	print_map(new_map);
}
