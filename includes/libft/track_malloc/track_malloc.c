/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:20:52 by albozkur          #+#    #+#             */
/*   Updated: 2024/08/20 18:16:57 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/*
 *	typedef	struct s_track_malloc t_track_malloc
 *	#include <stdlib.h>
 	-	void free(void *__ptr)
 *	void	*ft_calloc(size_t count, size_t size)
 *	void	track_malloc_lstadd_back(t_track_malloc **ptr, t_track_malloc *new)
 */

void	*track_malloc(int size, t_track_malloc **holder)
{
	void			*p;
	t_track_malloc	*new_node;

	p = ft_calloc(size, 1);
	if (!p)
		return (NULL);
	new_node = (t_track_malloc *)ft_calloc(sizeof(t_track_malloc), 1);
	if (!new_node)
	{
		free(p);
		return (NULL);
	}
	new_node->p = p;
	new_node->next = NULL;
	track_malloc_lstadd_back(holder, new_node);
	return (p);
}
