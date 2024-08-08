/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:44:29 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/08 16:46:48 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
// size_t

size_t	str_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
