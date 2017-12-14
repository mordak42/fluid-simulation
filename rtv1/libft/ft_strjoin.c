/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:30:43 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/24 17:42:30 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;
	size_t	n1;
	size_t	n2;

	if (!s1 || !s2)
		return (NULL);
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	if (!(r = ft_strnew(n1 + n2)))
		return (NULL);
	i = 0;
	while (i < n1)
	{
		r[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < n2)
	{
		r[i + n1] = s2[i];
		i++;
	}
	return (r);
}
