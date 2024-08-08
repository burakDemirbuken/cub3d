/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:08:21 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/08 17:12:34 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
// typedef t_file
#include "../include/libft/libft.h"
// ft_memset(void *b, int c, size_t len);
// ft_split(const char *s, char c);
#include <unistd.h>
// STDERR_FILENO

int	elements_valid(t_file *file, int i, int map_start, int count, int *flag)
{
	if (count != 6)
		return(ft_putstr_fd("cub3d: Element amount wrong\n", STDERR_FILENO), 0);
	if (map_start == i + 1)
		return (ft_putstr_fd("cub3d: No map found.\n", STDERR_FILENO), 0);
	if (!file->no || !file->no[0] || !file->so || !file->so[0]
		|| !file->we || !file->we[0] || !file->ea || !file->ea[0])
		return (ft_putstr_fd("cub3d: Missing elements.\n", STDERR_FILENO), 0);
}

// Sets the elements that are not the map.
// Returns the index of the first map element.
// Exits if there is an error.
int	set_first_half(t_file *file, char **content)
{
	int	i;
	int	map_start;
	int	count;
	int	flag[6];

	i = -1;
	count = 0;
	while (content[++i])
	{
		if (!ft_strncmp(content[i], "NO", 2) || !ft_strncmp(content[i], "SO", 2)
			|| !ft_strncmp(content[i], "WE", 2) || content[0] == 'C'
			|| !ft_strncmp(content[i], "EA", 2) || content[0] == 'F')
		{
			if (set_elements(content[i], file, flag))
				return (ft_strfree(content), free_file(file), exit(1), -1);
			map_start = i + 1;
			count++;
		}
	}
	if (!elements_valid(file, i, map_start, count))
		return (ft_strfree(content), free_file(file), exit(1), -1);
	return (map_start);
}

t_file	separate_content(char *line)
{
	t_file	file;
	char	**content;
	int		map_start;

	ft_memset(&file, 0, sizeof(t_file));
	content = ft_split(line, '\n');
	free(line);
	if (!content)
		return (perror("cub3d"), exit(1), file);
	map_start = set_first_half(&file, content);
	set_map_half(&file, content);
}
