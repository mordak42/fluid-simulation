/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 00:13:05 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/03 14:51:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "libft.h"

static char		*ft_fill_a(int length, int neg, long int tmp, int precision)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char) * length)))
		return (NULL);
	s[--length] = '\0';
	if (neg)
		s[0] = '-';
	while (length > neg)
	{
		s[--length] = (!precision--) ? '.' : tmp % 10 + '0';
		tmp /= (precision + 1) ? 10 : 1;
	}
	return (s);
}

char			*ft_dtoa(double n, int precision)
{
	long int		tmp;
	int				length;
	int				neg;
	long int		t;

	neg = (n < 0) ? 1 : 0;
	length = 0;
	tmp = (n * pow(10, precision));
	t = (long int)n;
	t = (t < 0) ? -t : t;
	tmp = (tmp < 0) ? -tmp : tmp;
	while (t)
	{
		t /= 10;
		length++;
	}
	length += (length == 0) ? 3 : 2;
	length = length + neg + precision;
	return (ft_fill_a(length, neg, tmp, precision));
}
