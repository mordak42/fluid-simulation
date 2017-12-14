/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 22:51:30 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 22:53:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_safe(const char *a, char **end_ptr, int *res)
{
	int ret;
	int i;
	int neg;

	ret = 0;
	i = 0;
	neg = 1;
	while (a[i] == ' ' || (a[i] >= 9 && a[i] <= 13))
		i++;
	if (a[i] == '-' || a[i] == '+')
	{
		if (a[i] == '-')
			neg *= -1;
		i++;
	}
	if (!(a[i] && ft_isdigit(a[i])))
		return (0);
	while (a[i] && ft_isdigit(a[i]))
	{
		ret = ret * 10 + a[i] - '0';
		i++;
	}
	*res = ret * neg;
	*end_ptr = (char*)a + i;
	return (1);
}
