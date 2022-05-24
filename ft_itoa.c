/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcomic <jcomic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:34:51 by jcomic            #+#    #+#             */
/*   Updated: 2021/12/21 16:34:52 by jcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static unsigned int	ft_nbr(unsigned int nb, int n)
{
	unsigned int	i;

	i = 0;
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	i++;
	if (n < 0)
		i = i + 1;
	return (i);
}

static unsigned int	ft_minus(int n )
{
	unsigned int	nb;

	if (n < 0)
		nb = (unsigned int)(-1 * n);
	else
		nb = (unsigned int)n;
	return (nb);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	nb;
	int				len;
	char			*s;

	nb = ft_minus(n);
	len = ft_nbr(nb, n);
	s = malloc(sizeof(char) * (len + 1));
	if (NULL == s)
		return (NULL);
	if (s != 0)
	{
		if (n < 0)
			s[0] = '-';
		i = len - 1 ;
		while (nb >= 10)
		{
			s[i--] = (char)(nb % 10 + '0');
			nb = nb / 10;
		}
		s[i] = (char)(nb % 10 + '0');
	}
	s[len] = '\0';
	return (s);
}
