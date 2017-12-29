/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 03:07:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "math.h"
#include "stdlib.h"
#include <mlx.h>
#include "libft.h"

void	mv_forward(t_cam *cam)
{
	cam->pos.x += cam->dir.x * 0.4;
	cam->pos.y += cam->dir.y * 0.4;
	cam->pos.z += cam->dir.z * 0.4;
}

void	mv_backward(t_cam *cam)
{
	cam->pos.x -= cam->dir.x * 0.4;
	cam->pos.y -= cam->dir.y * 0.4;
	cam->pos.z -= cam->dir.z * 0.4;
}

void	rot_arround_left(t_cam *cam)
{
	cam->pos = rot(cam->pos, -TETA * 3);
	cam->dir = rot(cam->dir, -TETA * 3);
}

void	rot_arround_right(t_cam *cam)
{
	cam->pos = rot(cam->pos, TETA * 3);
	cam->dir = rot(cam->dir, TETA * 3);
}

int		recalc_img(void *scene)
{
	t_env	*env;
	t_scene	*s;

	s = (t_scene *)scene;
	env = singleton_env();
	move_arows(env, s);
	if (env->forward)
		mv_forward(&s->cam);
	if (env->backward)
		mv_backward(&s->cam);
	if (env->key_r)
		rot_arround_left(&s->cam);
	if (env->key_t)
		rot_arround_right(&s->cam);
	if (env->rotx != 0 && env->indice_obj < s->objs_number)
		rot_obj(env, s, &rot_x, env->rotx);
	if (env->roty != 0 && env->indice_obj < s->objs_number)
		rot_obj(env, s, &rot_y, env->roty);
	if (env->rotz != 0 && env->indice_obj < s->objs_number)
		rot_obj(env, s, &rot_z, env->rotz);
	init_norm_cam_dir(&s->norm_vert, &s->norm_hor, s->cam.dir);
	return (0);
}
