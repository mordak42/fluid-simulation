/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp_double_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 17:03:22 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

float		norme_carre(cl_float3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float		scalar_product(cl_float3 u, cl_float3 v)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

cl_float3	normalize(cl_float3 v)
{
	return (div_vect(v, sqrt(norme_carre(v))));
}
