/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:54:59 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/09 14:58:57 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
// typedef t_file
// typedef t_color
// str_arrlen(char **arr);
#include "../include/libft/libft.h"
// ft_strfree(char **str);
// ft_putstr_fd(const char *s, int fd);
// ft_atoi(const char *str);
// ft_strtrim(char *s, char *set);
#include <unistd.h>
// STDERR_FILENO

// Checks if there is an error in the elements.
int	elements_valid(t_file *file, int i, int map_start, int count, int *flag)
{
	if (count != 6)
		return(ft_putstr_fd("cub3d: Wrong amount of elements.\n",
			STDERR_FILENO), 0);
	if (map_start == i + 1)
		return (ft_putstr_fd("cub3d: No map found.\n", STDERR_FILENO), 0);
	while (count--)
		if (flag[count] != 1)
			return (ft_putstr_fd("cub3d: Wrong amount of elements.\n",
				STDERR_FILENO), 0);
	if (!file->no || !file->no[0] || !file->so || !file->so[0]
		|| !file->we || !file->we[0] || !file->ea || !file->ea[0])
		return (ft_putstr_fd("cub3d: Missing elements.\n", STDERR_FILENO), 0);
}

// Sets file->f and file->c colors.
bool	set_color(char *content, t_color *color)
{
	char **rgb;

	if (!content)
		return (perror("cub3d"), 1);
	rgb = ft_split(content, ',');
	if (!rgb)
		return (perror("cub3d"), 1);
	if (str_arrlen(rgb) != 3)
		return (ft_strfree(rgb), ft_putstr_fdI("cub3d: Missing colors\n",
			STDERR_FILENO), 1);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	ft_strfree(rgb);
	if (!((color->r >= 0 && color->r < 256) && (color->g >= 0 && color->g < 256)
		&& (color->b >= 0 && color->b < 256)))
		return (ft_putstr_fd("cub3d: Invalid colors\n", STDERR_FILENO), 1);
	*color = rgb_to_color(color->r, color->g, color->b);
	free(content);
	return (true);
}

// Seperates the texture paths via ft_split.
// Returns 1 if there is an error.
bool	set_texture_paths(char *content, char ***texture)
{
	(*texture) = ft_split(content, ' ');
	if (!(*texture))
		return (perror("cub3d"), true);
	return (false);
}

// Sets an element that isn't the map.
// Returns 1 if there is an error.
int	set_elements(char *content, t_file *file, int *flag)
{
	if (!ft_strncmp(content, "NO", 2))
		return (flag[0]++, set_texture_paths(content + 2, &(file->no)));
	else if (!ft_strncmp(content, "SO", 2))
		return (flag[1]++, set_texture_paths(content + 2, &(file->so)));
	else if (!ft_strncmp(content, "WE", 2))
		return (flag[2]++, set_texture_paths(content + 2, &(file->we)));
	else if (!ft_strncmp(content, "EA", 2))
		return (flag[3]++, set_texture_paths(content + 2, &(file->ea)));
	else if (content[0] == 'F')
		return(flag[4]++, set_color(ft_strtrim(content + 1, " "), &(file->f)));
	else if (content[0] == 'C')
		return(flag[5]++, set_color(ft_strtrim(content + 1, " "), &(file->c)));
}
