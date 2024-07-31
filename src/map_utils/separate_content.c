/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:15:30 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/31 20:15:13 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include <unistd.h>

void	set_elements(char *element, t_map *map, int *count)
{
	(*count)++;
	if (!ft_strncmp(element, "NO", 2))
		map->no = get_texture(element);
	else if (!ft_strncmp(element, "SO", 2))
		map->so = get_texture(element);
	else if (!ft_strncmp(element, "EA", 2))
		map->ea = get_texture(element);
	else if (!ft_strncmp(element, "WE", 2))
		map->we = get_texture(element);
	else if (!ft_strncmp(element, "C", 1))
		map->c = get_colour(element);
	else if (!ft_strncmp(element, "F", 1))
		map->f = get_colour(element);
}

int	set_map(char **cont, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (cont[++i])
	{
		j = -1;
		while (cont[i][++j])
		{
			if (cont[i][j + 1] == '\0')
				cont[i][j] = '\0';
			else if (!(cont[i][j] == '0' || cont[i][j] == '1'
				|| cont[i][j] == 'N' || cont[i][j] == 'S'
				|| cont[i][j] == 'W' || cont[i][j] == 'E'
				|| cont[i][j] == ' '))
				return (ft_putstr_fd("Map has undefined elements\n",
					STDERR_FILENO), 1);
		}
	}
	map->map = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (map->map[++i])
		map->map[i] = ft_strdup(cont[i]);
	map->map[i] = NULL;
	return (0);
}

int	iterate_through_elements(char **f_cont, t_tmp_map *map)
{
	
}

t_tmp_map	separate_content(char *f_line)
{
	t_tmp_map	map;
	char		**f_cont;
	int			map_start;

	f_cont = ft_split(f_line, '\n');
	if (f_cont == NULL)
		return(perror("cub3d"), free(f_line), exit(1), map);
	map_start = count_elemnts(f_cont);
	set_map(f_cont + map_start, &map);
	return (map);
}
