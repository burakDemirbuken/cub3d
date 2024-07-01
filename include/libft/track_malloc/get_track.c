/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_track.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:18:30 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/06/23 15:24:40 by bdemirbu         ###   ########.fr       */
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
