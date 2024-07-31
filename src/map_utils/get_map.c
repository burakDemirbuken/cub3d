/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:44:29 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/31 14:07:49 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Checks the file extension. Exits if it's wrong.
void	is_cub(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len <= 4 || file_name[--len] != 'b' || file_name[--len] != 'u'
		|| file_name[--len] != 'c' || file_name[--len] != '.')
	{
		ft_putstr_fd("cub3d: File extension not .cub\n", STDERR_FILENO);
		exit (1);
	}
}

// Reads the file using get next line.
// It reallocates place for the 2d array pointer as it reads more lines.
// Returns the 2d char array.
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
		// check if this returns NULL to handle memory errors gracefully...
		content = ft_recalloc(content, sizeof(char *) * (index + 1),
			sizeof(char *) * (index + 2));
		ft_putnbr_fd(sizeof(char *) * (index + 2), 1);
		ft_putchar_fd('\n', 1);
		content[index++] = line;
		content[index] = NULL;
	}
	print_map(content);
	ft_putstr_fd("Map read\n", 1);
	return (content);
}

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

int	set_map(char **content, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (content[++i])
	{
		j = -1;
		while (content[i][++j])
		{
			if (content[i][j + 1] == '\0')
				content[i][j] = '\0';
			else if (!(content[i][j] == '0' || content[i][j] == '1'
				|| content[i][j] == 'N' || content[i][j] == 'S'
				|| content[i][j] == 'W' || content[i][j] == 'E'
				|| content[i][j] == ' '))
				return (ft_putstr_fd("Map has undefined elements\n",
					STDERR_FILENO), 1);
		}
	}
	map->map = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (map->map[++i])
		map->map[i] = ft_strdup(content[i]);
	map->map[i] = NULL;
	return (0);
}

t_map	 seperate_content(char **content)
{
	t_map	map;
	int	i;
	int	last;
	int	count;

	i = -1;
	count = 0;
	while(content[++i])
	{
		if (!ft_strncmp(content[i], "NO", 2) || !ft_strncmp(content[i], "SO", 2)
			|| !ft_strncmp(content[i], "EA", 2) || !ft_strncmp(content[i], "WE", 2)
			|| !ft_strncmp(content[i], "C", 1) || !ft_strncmp(content[i], "F", 1))
		{
			set_elements(content[i], &map, &count);
			last = i;
		}
	}
	if (count != 6)
		ft_putstr_fd("Wrong number of elements\n", STDERR_FILENO);
	if (i == last++)
		ft_putstr_fd("No map found\n", STDERR_FILENO);
	while (!ft_strncmp(content[last], "\n", 1))
		last++;
	set_map(content + last, &map);
	return (map);
}

void	get_map(char *file_name)
{
	char	**content;
	int		fd;
	t_map	map;

	is_cub(file_name);
	fd = open(file_name, O_RDONLY);
	if(fd < 0)
	{
		perror("cub3d");
		exit(1);
	}
	content = read_file(fd);
	close(fd);
	map = seperate_content(content);
	ft_strfree(content);
	map_checks(map.map);
}
