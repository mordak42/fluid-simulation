/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:35:02 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/15 02:32:35 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	start;
	size_t			len;

	i = 0;
	start = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[i] && ft_isblanckspace(s[i]))
		i++;
	start = i;
	while (s[i])
	{
		if (!(ft_isblanckspace(s[i])))
			len = i - start + 1;
		i++;
	}
	return (ft_strsub(s, start, len));
}
