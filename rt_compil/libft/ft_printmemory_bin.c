/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 15:58:05 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/05 23:49:56 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_bin(unsigned char c, int k)
{
	if (k == 0)
		return ;
	ft_putnbr_bin(c / 2, k - 1);
	ft_putchar(c % 2 == 0 ? '0' : '1');
}

void	ft_printmemory_bin(void *ptr, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		ft_putnbr_bin(*((unsigned char *)ptr), 8);
		write(1, " ", 1);
		ptr++;
		i++;
	}
}
