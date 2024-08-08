/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:14:11 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/26 16:29:11 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// texture part is not complete!
char	*get_texture(char *str)
{
	str += 2;
	while (*str == ' ')
		str++;
	// here will come the mlx image things!
	return (str);
}
