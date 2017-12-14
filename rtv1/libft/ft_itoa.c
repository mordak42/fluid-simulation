/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 02:59:43 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/15 00:21:20 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_zero(char *a)
{
	a[0] = '0';
	return (a);
}

static char	*ft_itoa_int_min(char *a)
{
	ft_strcpy(a, "-2147483648");
	return (a);
}

static int	ft_size_a(int n)
{
	int		i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*a;
	int		i;

	if (!(a = (char *)malloc(sizeof(char) * (ft_size_a(n) + 1))))
		return (NULL);
	i = ft_size_a(n);
	a[i] = '\0';
	i--;
	if (n == 0)
		return (ft_itoa_zero(a));
	if (n == -2147483648)
		return (ft_itoa_int_min(a));
	if (n < 0)
	{
		a[0] = '-';
		n *= -1;
	}
	while (n != 0)
	{
		a[i] = '0' + n % 10;
		n = n / 10;
		i--;
	}
	return (a);
}
