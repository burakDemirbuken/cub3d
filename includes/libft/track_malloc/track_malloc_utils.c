/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_malloc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:14:16 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:16:57 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/*
 *	typedef struct s_track_malloc t_track_malloc
 *	#include <stdlib.h>
	-	void free(void *__ptr)
 */

t_track_malloc	*track_malloc_lstlast(t_track_malloc *ptr)
{
	if (!ptr)
		return (0);
	while (ptr -> next)
		ptr = ptr -> next;
	return (ptr);
}

void	track_malloc_lstadd_back(t_track_malloc **ptr, t_track_malloc *new)
{
	t_track_malloc	*last;

	if (!*ptr)
	{
		*ptr = new;
	}
	else
	{
		last = track_malloc_lstlast(*ptr);
		last->next = new;
	}
}

int	settrack_varible(t_track_malloc *track, void *value)
{
	if (!track)
		return (1);
	free(track->p);
	track->p = value;
	return (0);
}
