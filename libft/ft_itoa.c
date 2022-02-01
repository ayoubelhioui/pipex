/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 09:21:51 by ael-hiou          #+#    #+#             */
/*   Updated: 2021/11/15 18:06:38 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(long c)
{
	int	cp;

	cp = 0;
	if (c < 0)
	{
		c *= -1;
		cp++;
	}
	while (c >= 0)
	{
		c = c / 10;
		cp++;
		if (c == 0)
			break ;
	}
	return (cp);
}

char	*fill(char *str, long n, int size)
{
	int	sign;

	sign = 0;
	str[size--] = '\0';
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
		sign = 1;
	}
	while (size > 0)
	{
		str[size] = (n % 10) + 48;
		n = n / 10;
		size--;
	}
	if (sign == 0)
		str[size] = (n % 10) + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*alocated;
	long int	c;

	c = n;
	size = ft_get_size(c);
	alocated = malloc(sizeof(char) * size + 1);
	if (!alocated)
		return (NULL);
	return (fill(alocated, c, size));
}
