/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 22:41:43 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

int			ft_str_is_clear(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isblanckspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

cl_float3	get_coordinates(cl_float3 res, char *value)
{
	char	*coord;

	coord = value;
	if (!(ft_strtof(coord, &coord, &res.x)))
		fatal("invalid coordinates");
	if (!(ft_strtof(coord, &coord, &res.y)))
		fatal("invalid coordinates");
	if (!(ft_strtof(coord, &coord, &res.z)))
		fatal("invalid coordinates");
	if (!ft_str_is_clear(coord))
		fatal("invalid coordinates");
	return (res);
}

double		get_rayon(char *value)
{
	float	res;

	if (!(ft_strtof(value, &value, &res)))
		fatal("invalid rayon");
	if (!ft_str_is_clear(value))
		fatal("invalid rayon");
	return (res);
}

size_t		get_hexa(char *value)
{
	size_t	res;

	if (!(ft_atoi_hexa(value, &value, &res)))
		fatal("invalid hexadecimal values");
	if (!ft_str_is_clear(value))
		fatal("invalid hexadecimal value");
	return (res);
}
