/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_malloc_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:05:12 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/06/23 15:17:13 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/*
 *	typedef struct s_track_malloc t_track_malloc
 *	#include
 	-	#define NULL ((void *)0)
	-	void	free(void *__ptr)
 *	void	*ft_calloc(size_t count, size_t size)
 *	void 	track_malloc_lstadd_back(t_track_malloc **ptr, t_track_malloc *new)
 */

int	track_malloc_add(void	*p, t_track_malloc **holder)
{
	t_track_malloc	*new;

	if (!p)
		return (1);
	new = (t_track_malloc *)ft_calloc(sizeof(t_track_malloc), 1);
	if (!new)
	{
		free(p);
		return (1);
	}
	new->p = p;
	new->next = NULL;
	track_malloc_lstadd_back(holder, new);
	return (0);
}
