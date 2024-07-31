/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:00:31 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/31 19:53:05 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft/libft.h"
#include "../../include/cub3d.h"
#include <unistd.h>

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
// It joins the line with ft_strjoin as it reads more lines.
// Returns the string.
char	*read_file(int fd)
{
	char	*content;
	char	*line;
	int		bytes;

	content = NULL;
	while (1)
	{
		bytes = get_next_line(fd, &line);
		if (bytes == 0)
			break ;
		else if (bytes == -1)
			return (close(fd), free(content), exit(1), NULL);
		content = ft_strjoin(content, line);
	}
	return (content);
}
