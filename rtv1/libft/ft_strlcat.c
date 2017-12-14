/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:14:29 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/15 02:19:54 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	res;

	if (ft_strlen(dst) < size)
		res = ft_strlen(dst) + ft_strlen(src);
	else
		res = ft_strlen(src) + size;
	n = size - ft_strlen(dst) - 1;
	if ((int)n > 0)
		ft_strncat(dst, src, n);
	return (res);
}
