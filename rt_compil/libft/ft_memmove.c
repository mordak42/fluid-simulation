/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:16:03 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/27 21:06:40 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memrevcpy(void *dest, const void *src, size_t n)
{
	unsigned int i;

	i = n - 1;
	while (i > 0)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i--;
	}
	((unsigned char*)dest)[0] = ((unsigned char*)src)[0];
	return (dest);
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	if (n == 0)
		return (dest);
	if (src > dest)
		ft_memcpy(dest, src, n);
	else if (src < dest)
		ft_memrevcpy(dest, src, n);
	return (dest);
}
