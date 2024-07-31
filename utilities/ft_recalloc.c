/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:09:34 by bkorkut           #+#    #+#             */
/*   Updated: 2024/07/25 16:18:43 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft/libft.h"
// #include <stdlib.h>

// Allocates memory for a new pointer. Copies the contents of the old one.
// User needs to consider '\0' caharacters at the end of strings themselves.
void	*ft_recalloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	index;
	void	*new_ptr;

	new_ptr = ft_calloc(sizeof(void *), new_size);
	index = 0;
	while (((char *)ptr) && index < new_size && index < old_size)
	{
		((char *)new_ptr)[index] = ((const char *)ptr)[index];
		index++;
	}
	free(ptr);
	return (new_ptr);
	// This beby need some error checks alright!
}
