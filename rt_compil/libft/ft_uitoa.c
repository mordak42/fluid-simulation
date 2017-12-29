/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 17:46:56 by vcombey           #+#    #+#             */
/*   Updated: 2017/01/27 17:47:12 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_zero(char *a)
{
	a[0] = '0';
	return (a);
}

static int	ft_size_ua(unsigned int n)
{
	int		i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_uitoa(unsigned int n)
{
	char			*a;
	unsigned int	i;

	i = ft_size_ua(n);
	if (!(a = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	a[i] = '\0';
	i--;
	if (n == 0)
		return (ft_itoa_zero(a));
	while (n != 0)
	{
		a[i] = '0' + n % 10;
		n = n / 10;
		i--;
	}
	return (a);
}
