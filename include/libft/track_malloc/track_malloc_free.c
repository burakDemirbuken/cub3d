/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_malloc_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:59:11 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/06/23 15:19:33 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/*
 *	#include <stdlib.h>
 	-	void free(void *__ptr)
 *	typedef struct s_track_malloc t_track_malloc
 */

void	track_malloc_free(t_track_malloc *ptr)
{
	t_track_malloc	*tmp;

	while (ptr != NULL)
	{
		tmp = ptr;
		if (ptr->p)
			free(ptr->p);
		ptr = ptr->next;
		free(tmp);
	}
}
