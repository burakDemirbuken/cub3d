/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_malloc_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:59:11 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:16:57 by bkorkut          ###   ########.fr       */
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
