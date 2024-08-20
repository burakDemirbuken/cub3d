/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_track.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:18:30 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:16:57 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/*
 *	typedef	struct s_track_malloc t_track_malloc
 */

t_track_malloc	*get_track(t_track_malloc *track, void *needle)
{
	while (track)
	{
		if (track->p == needle)
			return (track);
		track = track->next;
	}
	return (NULL);
}
