/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:09:34 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/25 06:42:07 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft/libft.h"
// #include <stdlib.h>

// Allocates memory for a new pointer. Copies the contents of the old one.
// User needs to consider '\0' caharacters at the end of strings themselves.
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	index;
	void	*new_ptr;

	new_ptr = malloc(sizeof(void *) * new_size);
	index = 0;
	while (index < new_size && index < old_size)
	{
		((char *)new_ptr)[index] = ((const char *)ptr)[index];
		index++;
	}
	free(ptr);
	return (new_ptr);
	// This beby need some error checks alright!
}
