/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:44:29 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/23 11:55:18 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/cub3d.h"
// #include "../include/libft/libft.h"

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

// char	**read_file(t_map *map, int fd)
// {
// 	int		bytes;
// 	char	*line;
// 	char	*tmp;
// 	char	*read_section[BUFFER_SIZE + 1];

// 	tmp = (char *)malloc(sizeof(char) * 1);
// 	tmp[0] = '\0';
// 	bytes = 1;
// 	while (bytes > 0)
// 	{
// 		bytes = read(fd, read_section, BUFFER_SIZE);
// 		if (bytes == 0 && !tmp || bytes == -1)
// 			return (perror("Empty file\n"), free(tmp), exit (1));
// 		read_section[bytes] = '\0';
// 		line = ft_strjoin(tmp, read_section);
// 		free(tmp);
// 		tmp = line;
// 	}
// 	if (tmp[0] == '\0')
// 		return (perror("Empty file\n"), free(tmp), exit (1));
// }

// t_map	get_map(char *file_name)
// {
// 	char	**file_content;
// 	t_map	map;

// 	is_cub(file_name);
// 	file_content = read_file();
// 	// map = seperate_elements(file_content);
// 	// elements_valid(map);
// 	// return (map);
// 	return(map);
// }
