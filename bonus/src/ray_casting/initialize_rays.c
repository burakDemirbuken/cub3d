/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:54:09 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/23 18:03:23 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
/*
 *	typedef struct s_cub3d t_cub3d
 *	#define RAY_COUNT	1920
 *	#define PERSPECTIVE	60.0f
 *	#define RAD_ANG		0.017453292519943295474371680597869271
 */

void	initialize_rays(t_cub3d *game)
{
	int	i;

	i = 0;
	while (i < RAY_COUNT)
	{
		game->rays[i].persp_angle = ((i + 1) * (PERSPECTIVE / RAY_COUNT))
			- (PERSPECTIVE / 2.0);
		game->rays[i].persp_angle *= RAD_ANG;
		i++;
	}
}
