/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:29:40 by vcombey           #+#    #+#             */
/*   Updated: 2016/12/07 20:26:03 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*n;
	void	*content_cpy;

	if (!(content_cpy = malloc(content_size)))
		return (NULL);
	if (!(n = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		n->content_size = 0;
		n->content = NULL;
	}
	else
	{
		n->content_size = content_size;
		ft_memcpy(content_cpy, content, content_size);
		n->content = content_cpy;
	}
	n->next = NULL;
	return (n);
}
