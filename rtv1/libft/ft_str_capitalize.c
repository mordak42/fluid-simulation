/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_capitalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 00:41:08 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/06 00:41:11 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_capitalize(char *s)
{
	unsigned int i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (ft_islower(s[i]))
			s[i] -= 32;
		i++;
	}
	return ;
}
