/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 21:49:27 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

cl_float3	rot(cl_float3 v, float teta)
{
	float tmp;

	tmp = v.x;
	v.x = v.x * cos(teta) - v.y * sin(teta);
	v.y = tmp * sin(teta) + v.y * cos(teta);
	return (v);
}

cl_float3	rot_x(cl_float3 v, float teta)
{
	float	mat[3][3];

	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[1][0] = 0;
	mat[1][1] = cos(teta);
	mat[1][2] = -sin(teta);
	mat[2][0] = 0;
	mat[2][1] = sin(teta);
	mat[2][2] = cos(teta);
	return (mat_mult_vect(mat, v));
}

cl_float3	rot_y(cl_float3 v, float teta)
{
	float	mat[3][3];

	mat[0][0] = cos(teta);
	mat[0][1] = 0;
	mat[0][2] = sin(teta);
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[2][0] = -sin(teta);
	mat[2][1] = 0;
	mat[2][2] = cos(teta);
	return (mat_mult_vect(mat, v));
}

cl_float3	rot_z(cl_float3 v, float teta)
{
	float	mat[3][3];

	mat[0][0] = cos(teta);
	mat[0][1] = -sin(teta);
	mat[0][2] = 0;
	mat[1][0] = sin(teta);
	mat[1][1] = cos(teta);
	mat[1][2] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	return (mat_mult_vect(mat, v));
}

cl_float3	rodrigues(cl_float3 input, cl_float3 v, float teta)
{
	cl_float3	res;
	float		mat[3][3];

	mat[0][0] = cos(teta) + (1 - cos(teta)) * v.x * v.x;
	mat[0][1] = (1 - cos(teta)) * v.x * v.y - sin(teta) * v.z;
	mat[0][2] = (1 - cos(teta)) * v.x * v.z + sin(teta) * v.y;
	mat[1][0] = (1 - cos(teta)) * v.x * v.y - sin(teta) * v.z;
	mat[1][1] = cos(teta) + (1 - cos(teta)) * v.y * v.y;
	mat[1][2] = (1 - cos(teta)) * v.y * v.z - sin(teta) * v.x;
	mat[2][0] = (1 - cos(teta)) * v.x * v.z - sin(teta) * v.y;
	mat[2][1] = (1 - cos(teta)) * v.y * v.z - sin(teta) * v.x;
	mat[2][2] = cos(teta) + (1 - cos(teta)) * v.z * v.z;
	res = mat_mult_vect(mat, input);
	return (res);
}
