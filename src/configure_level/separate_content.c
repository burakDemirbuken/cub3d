/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:08:21 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 08:17:25 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// typedef t_file
#include "../includes/libft/libft.h"
// ft_memset(void *b, int c, size_t len);
// ft_split(const char *s, char c);
#include <unistd.h>
// STDERR_FILENO

// Sets the elements that are not the map.
// Returns the index of the first map element.
// Exits if there is an error.
static int	set_first_half(t_file *file, char **content)
{
	int	i;
	int	map_start;
	int	count;
	int	flag[6];

	i = -1;
	count = 6;
	map_start = 0;
	while (count)
		flag[--count] = 0;
	while (content[++i])
	{
		if (!ft_strncmp(content[i], "NO", 2) || !ft_strncmp(content[i], "SO", 2)
			|| !ft_strncmp(content[i], "WE", 2) || content[i][0] == 'C'
			|| !ft_strncmp(content[i], "EA", 2) || content[i][0] == 'F')
		{
			if (set_elements(content[i], file, flag))
				return (ft_strfree(content), free_file(file), exit(1), -1);
			map_start = i + 1;
			count++;
		}
	}
	if (!elements_valid(file, (i + 1 == map_start), count, flag))
		return (ft_strfree(content), free_file(file), exit(1), -1);
	return (map_start);
}

// Counts the map length and checks for undefined elements.
static int	inspect_map(t_file *file, char **content)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (content[++i])
	{
		j = -1;
		while (content[i][++j])
		{
			if (content[i][j] == NORTH || content[i][j] == SOUTH
				|| content[i][j] == WEST || content[i][j] == EAST)
				count++;
			else if (!(content[i][j] == '0' || content[i][j] == '1'
				|| content[i][j] == DOOR || content[i][j] == ' '
				|| content[i][j] == '\0'))
				return (ft_putstr_fd(ERR_MUNDEF, STDERR_FILENO), -1);
		}
		if (file->map_width < j)
			file->map_width = j;
	}
	file->map_height = i;
	return (count);
}

// Copies the map off of file content to the file struct.
static bool	copy_content_map(t_file *file, char **content)
{
	int	i;

	i = -1;
	file->map = (char **)ft_calloc(file->map_height + 1, sizeof(char *));
	if (!file->map)
		return (perror(ERR_CUB3D), 0);
	i = -1;
	while (content[++i])
	{
		file->map[i] = ft_strdup(content[i]);
		if (!file->map[i])
			return (perror(ERR_CUB3D), 0);
	}
	file->map[i] = NULL;
	return (1);
}

// Sets the map part.
// Exits if there is an error.
static bool	set_map_half(t_file *file, char **content, int map_start)
{
	int	count;

	count = inspect_map(file, content + map_start);
	if (count == -1)
		return (ft_strfree(content), free_file(file), exit(1), 1);
	if (count != 1)
		return (ft_putstr_fd(ERR_PUNDEF, STDERR_FILENO),
			ft_strfree(content), free_file(file), exit(1), 1);
	if (file->map_height < 3 || file->map_width < 3)
		return (ft_putstr_fd(ERR_MSMALL, STDERR_FILENO),
			ft_strfree(content), free_file(file), exit(1), 1);
	if (!copy_content_map(file, content + map_start))
		return (ft_strfree(content), free_file(file), exit(1), 1);
	return (0);
}

// Seperates the file content.
t_file	separate_content(char *line)
{
	t_file	file;
	char	**content;
	int		map_start;

	ft_memset(&file, 0, sizeof(t_file));
	content = ft_split(line, '\n');
	free(line);
	if (!content)
		return (perror(ERR_CUB3D), exit(1), file);
	map_start = set_first_half(&file, content);
	set_map_half(&file, content, map_start);
	ft_strfree(content);
	return (file);
}
