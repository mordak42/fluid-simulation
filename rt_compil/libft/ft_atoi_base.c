/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 22:33:58 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 22:45:38 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_hexa(const char *a, char **end_ptr, size_t *res)
{
	int		ret;
	int		i;
	size_t	tmp;

	ret = 0;
	i = 0;
	while (a[i] == ' ' || (a[i] >= 9 && a[i] <= 13))
		i++;
	if (a[i] != '0' || a[i + 1] != 'X')
		return (0);
	i += 2;
	while (a[i] && (ft_isdigit(a[i]) || (a[i] >= 'A' && a[i] <= 'F')))
	{
		tmp = (ft_isdigit(a[i])) ? a[i] - '0' : a[i] - 'A' + 10;
		ret = ret * 16 + tmp;
		i++;
	}
	*res = ret;
	*end_ptr = (char *)a + i;
	return (1);
}
