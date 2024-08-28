/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:49:08 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/28 17:45:28 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>
// double cos(double)

static void inline	print_gradian_vertical(t_cub3d *game, t_image img, int y, t_color color)
{
	double		i;
	t_color t_color;

	i = 0;
	while (i <= WINDOWS_WIDTH / 2)
	{
		t_color = color;
		if (game->shadow)
			t_color = blackout(t_color, 1.0 - (i / ((double)WINDOWS_WIDTH / 2.0) + 0.42));
		put_pixel_to_image(img, i, y, t_color.hex);
		put_pixel_to_image(img, WINDOWS_WIDTH - i, y, t_color.hex);
		i++;
	}
}

void inline	paint_floor_ceiling(t_cub3d *game)
{
	int				i;
	t_color			color;

	i = 0;
	while (i <= WINDOWS_HEIGHT / 2)
	{
		color = game->floor;
		if (game->shadow)
			color = blackout(color, 1.0 - (i / (((double)WINDOWS_HEIGHT / 2.0))) + 0.32);
		print_gradian_vertical(game, game->images.background,
			WINDOWS_HEIGHT / 2 - i, color);
		color = game->ceiling;
		if (game->shadow)
			color = blackout(color, 1.0 - (i / ((double)WINDOWS_HEIGHT / 2.0)) + 0.32);
		print_gradian_vertical(game, game->images.background,
			WINDOWS_HEIGHT / 2 + i, color);
		i++;
	}
}
