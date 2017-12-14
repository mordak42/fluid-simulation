/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 17:06:51 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	calc_delta(float a, float b, float c)
{
	return (b * b - 4 * a * c);
}

float	ft_min(float u, float v)
{
	return (u < v ? u : v);
}

float	ft_abs_float(float u)
{
	return (u > 0 ? u : -u);
}

float	ft_min_positiv(float a, float b)
{
	if (a < 0 && b > 0)
		return (b);
	if (a > 0 && b < 0)
		return (a);
	return (ft_min(a, b));
}
