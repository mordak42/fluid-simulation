/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 19:54:49 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 20:59:24 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rot_obj(t_env *env, t_scene *s, cl_float3 (f_rot)(cl_float3, float),\
		int sign_rot)
{
	s->objs[env->indice_obj].dirx = f_rot(s->objs[env->indice_obj].dirx, \
			TETA_ROT * sign_rot);
	s->objs[env->indice_obj].diry = f_rot(s->objs[env->indice_obj].diry, \
			TETA_ROT * sign_rot);
	s->objs[env->indice_obj].dirz = f_rot(s->objs[env->indice_obj].dirz, \
			TETA_ROT * sign_rot);
	env->obj_has_changed = 1;
}
