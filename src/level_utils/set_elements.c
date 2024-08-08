/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:54:59 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/08 15:24:42 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
// adasf
#include "../include/libft/libft.h"



t_color	rgb_to_color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.hex = (r << 16) | (g << 8) | b;
	return (color);
}

t_color	hex_to_color(unsigned int hex)
{
	t_color	color;

	color.r = (hex & 0xFF0000) >> 16;
	color.g = (hex & 0xFF00) >> 8;
	color.b = hex & 0xFF;
	color.hex = hex;
	return (color);
}

bool	set_color(char *content, t_color *color)
{
	char **rgb;

	rgb = ft_split(content, ',');
	if (!rgb)
		return (perror("cub3d"), 1);
	// if the number of rgb is wrong...
	// HERE YOU ARE
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	ft_strfree(rgb);
	// if the rgb are bigger than 255...
	*color = rgb_to_color(color->r, color->g, color->b);
	return (true);
}

// Seperates the texture paths via ft_split.
// returns 1 if there is an error.
bool	set_texture_paths(char *content, char ***texture)
{
	(*texture) = ft_split(content, ' ');
	if (!(*texture))
		return (perror("cub3d"), true);
	return (false);
}

// Sets an element that isn't the map.
// returns 1 if there is an error.
int	set_elements(char *content, t_file *file)
{
	if (!ft_strncmp(content, "NO", 2))
		return (set_texture_paths(content + 2, &(file->no)));
	else if (!ft_strncmp(content, "SO", 2))
		return (set_texture_paths(content + 2, &(file->so)));
	else if (!ft_strncmp(content, "WE", 2))
		return (set_texture_paths(content + 2, &(file->we)));
	else if (!ft_strncmp(content, "EA", 2))
		return (set_texture_paths(content + 2, &(file->ea)));
	else if (content[0] == 'F')
		return(set_color(ft_strtrim(content + 1, " "), &(file->f)));
	else if (content[0] == 'C')
		return(set_color(ft_strtrim(content + 1, " "), &(file->c)));
}
