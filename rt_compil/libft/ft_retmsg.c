/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 20:00:24 by vcombey           #+#    #+#             */
/*   Updated: 2016/12/30 20:00:27 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_retmsg(char *message, int sortie)
{
	if (sortie == 2)
	{
		ft_putendl_fd(message, 2);
		return (1);
	}
	ft_putendl(message);
	return (0);
}

void	ft_exit(char *message, int sortie)
{
	if (sortie == 2)
	{
		ft_putendl_fd(message, 2);
		exit(1);
	}
	ft_putendl(message);
	exit(0);
}
