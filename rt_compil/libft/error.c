/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:51:01 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/05 23:57:14 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"
#include <stdio.h>

void	ft_error(char *str, char *name)
{
	ft_putstr_fd(str, 2);
	perror(name);
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
