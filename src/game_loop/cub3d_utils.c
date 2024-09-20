/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:41:28 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/19 11:27:43 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/*
 *	typedef struct s_image t_image
 */

void	put_pixel_to_image(t_image img, int x, int y, unsigned int color)
{
	if (img.height > y && y >= 0 && img.width > x && x >= 0)
		*(unsigned int *)(img.data
				+ (int)((y * img.line_lenght) + (x * (img.bits_per_pixel / 8))))
			= color;
}

unsigned int	get_pixel_color(t_image img, int x, int y)
{
	if (x < 0 || y < 0 || x >= img.width || y >= img.height)
		return (0);
	return (*(unsigned int *)(img.data
		+ (int)((y * img.line_lenght) + (x * (img.bits_per_pixel / 8)))));
}
