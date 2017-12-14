/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 03:03:53 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/15 00:27:27 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] && s2[j] && s1[i + j] == s2[j] && i + j < n)
			j++;
		if (j == ft_strlen(s2))
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
