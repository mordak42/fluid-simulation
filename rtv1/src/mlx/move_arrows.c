/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 19:49:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 01:55:17 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rot_right(t_cam *cam)
{
	cam->dir = rot(cam->dir, TETA);
}

void	mv_up(t_cam *cam, t_scene *scene)
{
	cam->dir = rodrigues(cam->dir, scene->norm_hor, -TETA);
	cam->dir = normalize(cam->dir);
}

void	mv_down(t_cam *cam, t_scene *scene)
{
	cam->dir = rodrigues(cam->dir, scene->norm_hor, TETA);
	cam->dir = normalize(cam->dir);
}

void	rot_left(t_cam *cam)
{
	cam->dir = rot(cam->dir, -TETA);
}

void	move_arows(t_env *env, t_scene *s)
{
	if (env->up)
		mv_up(&s->cam, s);
	if (env->down)
		mv_down(&s->cam, s);
	if (env->left)
		rot_right(&s->cam);
	if (env->right)
		rot_left(&s->cam);
}
