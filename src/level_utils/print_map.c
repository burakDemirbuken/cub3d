/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:07:31 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/06 16:36:25 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 6 elements come before the map
// All six elements need to be peresent

#include "../../include/cub3d.h"
#include "../../include/libft/libft.h"

void	print_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		ft_putstr_fd(map[i], 1);
		ft_putstr_fd("e\n", 1);
		i++;
	}
}