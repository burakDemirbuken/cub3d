/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:58:38 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/20 18:16:57 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lenght;
	char	*a;

	lenght = ft_strlen(s1) + ft_strlen(s2) + 1;
	a = (char *)malloc(sizeof(char) * (lenght));
	if (!a)
		return (0);
	ft_strlcpy(a, s1, lenght);
	ft_strlcat(a, s2, lenght);
	return (a);
}
