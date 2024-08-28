/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:54:09 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/28 15:29:18 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
