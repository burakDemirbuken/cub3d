/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_separate_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:15:30 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/08 14:52:17 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include <unistd.h>

// Sets all elements except the map.
// returns 1 if there is an error.
int	set_elements(char *element, t_tmp_map *map)
{
	if (!ft_strncmp(element, "NO", 2))
		return (set_single_element(&(map->no), element + 2));
	else if (!ft_strncmp(element, "SO", 2))
		return (set_single_element(&(map->so), element + 2));
	else if (!ft_strncmp(element, "EA", 2))
		return (set_single_element(&(map->ea), element + 2));
	else if (!ft_strncmp(element, "WE", 2))
		return (set_single_element(&(map->we), element + 2));
	else if (!ft_strncmp(element, "C", 1))
		return (map->c = get_colour(element), 0);
	else if (!ft_strncmp(element, "F", 1))
		return (map->f = get_colour(element), 0);
	else
		return (ft_putstr_fd("Invalid element.\n", STDERR_FILENO), 1);

	// This boi needs a revision where colours are.
}

// Makes a copy of the map in file content.
// Exits if there is an error.
static void	copy_map(char **cont, t_tmp_map *map)
{
	int	i;

	map->map = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (map->map == NULL)
		return (perror("cub3d"), ft_strfree(cont), free_tmp_map(map), exit(1));
	i = -1;
	while (cont[++i])
	{
		map->map[i] = ft_strdup(cont[i]);
		if (map->map[i] == NULL)
			return (perror("cub3d"), ft_strfree(cont),
				free_tmp_map(map), exit(1));
	}
	map->map[i] = NULL;
}

// Checks for undefined elements and counts player starting positions.
// Returns the number of player starting positions.
// Sets the width and height of the tmp_map.
int	check_through_map(char **cont, t_tmp_map *map)
{
	int	count;
	int	i;
	int	j;

	i = -1;
	count = 0;
	while (cont[++i])
	{
		j = -1;
		while (cont[i][++j])
		{
			if (cont[i][j] == 'N' || cont[i][j] == 'S'
				|| cont[i][j] == 'W' || cont[i][j] == 'E')
				count++;
			else if (!(cont[i][j] == '0' || cont[i][j] == '1'
				|| cont[i][j] == ' ' || cont[i][j] == '\0'))
				return (ft_putstr_fd("Undefined elements.\n", STDERR_FILENO),
					ft_strfree(cont), free_tmp_map(map), exit(1), -1);
		}
		if (map->width < j)
			map->width = j;
	}
	map->height = i;
	return (count);
}

// Checks if the elements are valid.
int	elements_valid(t_tmp_map *map, int i, int map_start, int count)
{
	if (count != 6)
		return (ft_putstr_fd("Wrong number of elements.\n", STDERR_FILENO), 0);
	if (map_start == i + 1)
		return (ft_putstr_fd("No map found.\n", STDERR_FILENO), 0);
	// THIS PART NEEDS AN UPDATE!!!
	if (!map->no || !map->so || !map->we || !map->ea)
		return (ft_putstr_fd("Missing elements.\n", STDERR_FILENO), 0);
	return (1);
}

// Sets the elements to the tmp_map struct.
// If there is nothing missing,
// returns the index of the first element of the map.
int	iterate_through_elements(char **cont, t_tmp_map *map)
{
	int	i;
	int	count;
	int	map_start;

	i = -1;
	count = 0;
	while (cont[++i])
	{
		if (!ft_strncmp(cont[i], "NO", 2) || !ft_strncmp(cont[i], "SO", 2)
			|| !ft_strncmp(cont[i], "WE", 2) || !ft_strncmp(cont[i], "EA", 2)
			|| !ft_strncmp(cont[i], "F", 1) || !ft_strncmp(cont[i], "C", 1))
		{
			if (set_elements(cont[i], map))
				return (ft_strfree(cont), free_tmp_map(map), exit(1), -1);
			map_start = i + 1;
			count++;
		}
	}
	if (!elements_valid(map, i, map_start, count))
		return (ft_strfree(cont), free_tmp_map(map), exit(1), -1);
	return (map_start);
}

t_file	separate_content(char *line)
{
	t_file	file_content;
	char	**f_cont;
	int		map_start;
	int		count;

	// initialize_tmp_map(&map);
	// f_cont = ft_split(f_line, '\n');
	// if (f_cont == NULL)
	// 	return(perror("cub3d"), free(f_line), exit(1), map);
	// free(f_line);
	map_start = iterate_through_elements(f_cont, &map);
	count = check_through_map(f_cont + map_start, &map);
	if (count != 1)
		return (ft_putstr_fd("Player position undefined.\n", STDERR_FILENO),
			ft_strfree(f_cont), free_tmp_map(&map), exit(1), map);
	copy_map(f_cont + map_start, &map);
	ft_strfree(f_cont);
	return (map);
}
