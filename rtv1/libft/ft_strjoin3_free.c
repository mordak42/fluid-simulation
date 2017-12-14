/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:25:42 by vcombey           #+#    #+#             */
/*   Updated: 2017/01/28 15:36:51 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_strdelete(char *s1, char *s2, char *s3, int delete)
{
	if (delete == 1)
		free(s3);
	if (delete == 2)
		free(s2);
	else if (delete == 4)
		free(s1);
}

char			*ft_strjoin3_free(char *s1, char *s2, char *s3, int del)
{
	char	*r;
	size_t	i;
	size_t	n1;
	size_t	n2;
	size_t	n3;

	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	n3 = ft_strlen(s3);
	if (!(s1) || !(s2) || !(s3))
		return (NULL);
	if (!(r = ft_strnew(n1 + n2 + n3)))
		return (NULL);
	i = -1;
	while (++i < n1)
		r[i] = s1[i];
	i = -1;
	while (++i < n2)
		r[i + n1] = s2[i];
	i = -1;
	while (++i < n3)
		r[i + n1 + n2] = s3[i];
	ft_strdelete(s1, s2, s3, del);
	return (r);
}
