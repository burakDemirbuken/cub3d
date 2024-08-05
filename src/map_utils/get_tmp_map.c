/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tmp_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:44:29 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/03 14:53:50 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void	get_tmp_map(char *file_name)
{
	char		*f_line;
	int			fd;
	t_tmp_map	tmp_map;
	t_map		map;

	is_cub(file_name);
	fd = open(file_name, O_RDONLY);
	if(fd < 0)
		return (perror("cub3d"), exit(1));
	f_line = read_file(fd);
	close(fd);
	tmp_map = separate_content(f_line);
	map = set_actual_map(&tmp_map);
	(void)map;
}
