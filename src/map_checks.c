/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:44:29 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/25 15:05:39 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

// void	is_cub(char *file_name)
// {
// 	int		len;

// 	len = ft_strlen(file_name);
// 	if (len <= 4 || file_name[--len] != 'b' || file_name[--len] != 'u'
// 		|| file_name[--len] != 'c' || file_name[--len] != '.')
// 	{
// 		perror("File extension not .ber\n");
// 		exit (1);
// 	}
// }

// void	elements_valid(char **map)
// {
// 	texture_path_reachable();
// 	surround_walls();
// 	no_undefined_chars();
// }

char	**read_file(int fd)
{
	char	**file_content;
	char	*line;
	size_t	index;

	file_content = NULL;
	// check get_next line for error cases!
	// assuming how gnl works.
	index = 0;
	while (get_next_line(fd, &line) > 0)
	{
		file_content = ft_realloc(file_content, sizeof(char *) * index, sizeof(char *) * index + 1);
		file_content[index++] = line;
		file_content[index] = NULL;
	}
	return (file_content);
}

// 6 elements come before the map
// All six elements need to be peresent

// static void	path_finder(t_map *map, int y, int x)
// {
// 	if (map->virtual_map[y][x] == '1')
// 		return ;
// 	else if (map->virtual_map[y][x] == 'C')
// 		map->c_count[1]++;
// 	else if (map->virtual_map[y][x] == 'E')
// 		map-> e_count[1]++;
// 	else if (map->virtual_map[y][x] != 'P' && map->virtual_map[y][x] != '0')
// 		return (write(2, "The map has undefined elements\n", 31),
// 			free_map(map), exit(1));
// 	map->virtual_map[y][x] = '1';
// 	path_finder(map, y, x - 1);
// 	path_finder(map, y - 1, x);
// 	path_finder(map, y, x + 1);
// 	path_finder(map, y + 1, x);
// }

unsigned int	rgb_to_hex(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

unsigned int get_colour(char *str)
{
	int	red;
	int	green;
	int	blue;

	while (!(*str >= '0' && *str <= '9'))
		str++;
	red = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	while (!(*str >= '0' && *str <= '9'))
		str++;
	green = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	while (!(*str >= '0' && *str <= '9'))
		str++;
	blue = ft_atoi(str);
	// if (red / 256 != 0 | green / 256 != 0 | blue / 256 != 0)
	// 	; // NEEDS A BIG FAT ERROR CHECK!
	return (rgb_to_hex(red, green, blue));
}


t_map	seperate_elements(char **file_content)
{
	int	i;

	i = 0;
	while(file_content[i]);
}

t_map	get_map(char *file_name)
{
	char	**file_content;
	int		fd;
	t_map	map;

	is_cub(file_name);
	fd = open(file_name, O_RDONLY);
	file_content = read_file(fd);
	close(fd);
	map = seperate_elements(file_content);

	// int i = 0;
	// map.map = file_content;
	// while (file_content[i])
	// {
	// 	printf("%s", file_content[i++]);
	// }
	// elements_valid(map);
	// return (map);
	return(map);
}
