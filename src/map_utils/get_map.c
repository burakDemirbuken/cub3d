/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:44:29 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/25 20:32:29 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

void	is_cub(char *file_name)
{
	int		len;

	len = ft_strlen(file_name);
	if (len <= 4 || file_name[--len] != 'b' || file_name[--len] != 'u'
		|| file_name[--len] != 'c' || file_name[--len] != '.')
	{
		perror("File extension not .ber\n");
		exit (1);
	}
}

// void	elements_valid(char **map)
// {
// 	texture_path_reachable();
// 	surround_walls();
// 	no_undefined_chars();
// }

char	**read_file(int fd)
{
	char	**content;
	char	*line;
	size_t	index;

	content = NULL;
	// check get_next line for error cases!
	// assuming how gnl works.
	index = 0;
	while (get_next_line(fd, &line) > 0)
	{
		content = ft_recalloc(content, sizeof(char *) * index,
			sizeof(char *) * index + 1);
		content[index++] = line;
		content[index] = NULL;
	}
	return (content);
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

t_tmp_map	set_elements(char *element)
{
	t_tmp_map	map;
	int	i;
	int	non;

	i = -1;
	non = 0;
	while(content[++i])
	{
		if (!ft_strncmp(content[i], "NO", 2))
			map.no = get_texture(content[i]);
		else if (!ft_strncmp(content[i], "SO", 2))
			map.so = get_texture(content[i]);
		else if (!ft_strncmp(content[i], "EA", 2))
			map.ea = get_texture(content[i]);
		else if (!ft_strncmp(content[i], "WE", 2))
			map.we = get_texture(content[i]);
		else if (!ft_strncmp(content[i], "C", 1))
			map.c = get_colour(content[i]);
		else if (!ft_strncmp(content[i], "F", 1))
			map.f = get_colour(content[i]);
		else
			non++;
	}
	// needs proper exit
	if (i - non != 6)
		ft_putstr_fd("The number of element is wrong\n", STDERR_FILENO);
	return (map);
}

void	function(char **content)
{
	int	i = -1;
	int	last;
	while(content[++i])
	{
		if (!ft_strncmp(content[i], "NO", 2) || !ft_strncmp(content[i], "SO", 2)
			|| !ft_strncmp(content[i], "EA", 2) || !ft_strncmp(content[i], "WE", 2)
			|| !ft_strncmp(content[i], "C", 1) || !ft_strncmp(content[i], "F", 1))
		{
			set_elements(content[i]);
			last = i;
		}
	}
	if (i == last)
		ft_putstr_fd("No map found\n", STDERR_FILENO);
	i = last;
	while (!ft_strncmp(content[i], "\n", 1))
		i++;
	map.map = content + i;
}

t_map	get_map(char *file_name)
{
	char	**file_content;
	int		fd;
	t_map	map;
	t_tmp_map tmp_map;

	is_cub(file_name);
	fd = open(file_name, O_RDONLY);
	file_content = read_file(fd);
	close(fd);
	tmp_map = count_elements(file_content);

	// elements_valid(map);
	// return (map);

	(void)tmp_map;
	map.map = file_content;
	return(map);
}
