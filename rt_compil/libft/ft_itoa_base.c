/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 13:01:14 by exam              #+#    #+#             */
/*   Updated: 2017/02/06 00:37:10 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	united(intmax_t value, int base)
{
	int res;

	res = value % base;
	if (res < 0)
		res = -res;
	if (res <= 9)
		return ('0' + res % base);
	else if (res == 10)
		return ('a');
	else if (res == 11)
		return ('b');
	else if (res == 12)
		return ('c');
	else if (res == 13)
		return ('d');
	else if (res == 14)
		return ('e');
	else
		return ('f');
}

char	*ft_itoa_base10(intmax_t value, int base)
{
	int			i;
	intmax_t	nb;
	char		*str;

	i = 1;
	nb = value;
	if (base <= 1 || base > 16)
		return (NULL);
	while (nb / base != 0)
	{
		nb = nb / base;
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	str[i + 1] = '\0';
	str[0] = '-';
	nb = value;
	while (i > 0)
	{
		str[i] = united(nb, base);
		nb = nb / base;
		i--;
	}
	return (str);
}

char	*ft_itoa_base(intmax_t value, int base)
{
	int			i;
	intmax_t	nb;
	char		*str;

	i = 0;
	nb = value;
	if (base == 10 && nb < 0)
		return (ft_itoa_base10(value, base));
	if (base <= 1 || base > 16)
		return (NULL);
	while (++i && (nb / base != 0))
		nb = nb / base;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	i--;
	nb = value;
	while (i > -1)
	{
		str[i] = united(nb, base);
		nb = nb / base;
		i--;
	}
	return (str);
}
