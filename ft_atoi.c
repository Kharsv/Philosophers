/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:34:40 by jcomic            #+#    #+#             */
/*   Updated: 2021/12/21 16:34:43 by jcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*ft_move(const char *str)
{
	while (*str == ' ' || *str == '\n' || *str == '\t' \
	|| *str == '\r' || *str == '\v' || *str == '\f')
		++str;
	return ((char *)str);
}

long long int	ft_maxmin(long long int n)
{
	if (n < -9223372036854775807)
		return (0);
	if (n > 9223372036854775807)
		return (-1);
	else
		return (n);
}

int	ft_atoi(const char *str)
{
	long long int	result;
	int				sign;
	int				digit;

	result = 0;
	sign = 1;
	str = ft_move(str);
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		++str;
	while (*str >= '0' && *str <= '9')
	{	
		result = result * 10;
		digit = *str - '0';
		result = result + (digit * sign);
		if (result < -2147483648 || result > 2147483647)
		{
			result = ft_maxmin(result);
			break ;
		}
		++str;
	}
	return (result);
}
