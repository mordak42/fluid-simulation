/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 00:27:37 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/15 02:41:09 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*r;
	unsigned int	i;

	if (!(r = ft_strnew(len)))
		return (NULL);
	i = 0;
	if (!s)
		return (NULL);
	if (start + len > ft_strlen(s))
		return (NULL);
	while (i < len)
	{
		r[i] = s[start + i];
		i++;
	}
	return (r);
}
