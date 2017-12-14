/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 00:18:31 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/03 20:45:04 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_strdelete(char *s1, char *s2, int delete)
{
	if (delete == 3)
	{
		free(s1);
		free(s2);
	}
	if (delete == 1)
		free(s1);
	else if (delete == 2)
		free(s2);
}

char			*ft_strjoin_free(char *s1, char *s2, int delete)
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
	i = -1;
	while (++i < n1)
		r[i] = s1[i];
	i = -1;
	while (++i < n2)
		r[i + n1] = s2[i];
	ft_strdelete(s1, s2, delete);
	return (r);
}
