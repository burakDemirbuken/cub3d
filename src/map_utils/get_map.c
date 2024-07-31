/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:44:29 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/31 20:02:51 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void	get_map(char *file_name)
{
	char		*f_line;
	int			fd;
	t_tmp_map	tmp_map;

	is_cub(file_name);
	fd = open(file_name, O_RDONLY);
	if(fd < 0)
		return (perror("cub3d"), exit(1));
	f_line = read_file(fd);
	close(fd);
	tmp_map = separate_content(f_line);
	free(f_line);
}
