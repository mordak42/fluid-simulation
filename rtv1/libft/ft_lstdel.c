/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:18:07 by vcombey           #+#    #+#             */
/*   Updated: 2016/11/09 18:14:52 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list **next;

	next = &((*alst)->next);
	if ((*alst) == NULL)
		return ;
	else
	{
		ft_lstdel(next, del);
		ft_lstdelone(alst, del);
	}
}
