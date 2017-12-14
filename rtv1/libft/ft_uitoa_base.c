/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 00:40:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/06 00:40:25 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	united(uintmax_t value, int base)
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

char		*ft_uitoa_base(uintmax_t value, int base)
{
	int			i;
	uintmax_t	nb;
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
