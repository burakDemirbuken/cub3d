/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:15:37 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/05 17:40:14 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft/libft.h"

void	flood_fill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || map[y] == NULL || map[y][x] == '\0')
		return ;
	else if (map[y][x] == '1')
		return ;
	else if (map[y][x] == ' ')
		map[y][x] = '1';
	else if (map[y][x] == '0')
		ft_putstr_fd("cub3d: Map must be surrounded by walls\n", 2), exit(1);
	else
		ft_putstr_fd("cub3d: The map has undefined elements\n", 2), exit(1);
	flood_fill(map, y, x - 1);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y + 1, x);
}
