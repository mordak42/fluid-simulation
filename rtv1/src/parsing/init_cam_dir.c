/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 19:36:09 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 23:40:16 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	init_norm_cam_dir(cl_float3 *norm_vert, cl_float3 *norm_hor,\
		cl_float3 dir)
{
	dir = normalize(dir);
	*norm_hor = rot(dir, M_PI / 2);
	norm_hor->z = 0;
	*norm_hor = normalize(*norm_hor);
	*norm_vert = vectorial_product(dir, *norm_hor);
	*norm_hor = normalize(*norm_hor);
	*norm_vert = normalize(*norm_vert);
	if (dir.z == 1 || dir.z == -1)
	{
		*norm_hor = (cl_float3){.x = 1, .y = 0, .z = 0};
		*norm_hor = (cl_float3){.x = 0, .y = 1, .z = 0};
	}
}

void	get_vecteur(t_obj *new, char *line)
{
	new->dirz = get_coordinates(new->dirz, line);
	if (new->dirz.x == 0 && new->dirz.y == 0)
	{
		new->dirx = (cl_float3){.x = 1, .y = 0, .z = 0};
		new->diry = (cl_float3){.x = 0, .y = 1, .z = 0};
		return ;
	}
	new->dirx = rot(new->dirz, M_PI / 2);
	new->dirx.z = 0;
	new->dirz = normalize(new->dirz);
	new->diry = vectorial_product(new->dirz, new->dirx);
	new->dirx = normalize(new->dirx);
	new->diry = normalize(new->diry);
}
