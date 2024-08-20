/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:37:41 by bdemirbu          #+#    #+#             */
/*   Updated: 2023/10/16 20:14:51 by bdemirbu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_atoi(const char *str)
{
	long int	neg;
	long int	result;
	int			i;

	result = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * neg);
}
