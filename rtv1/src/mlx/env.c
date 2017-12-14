/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 00:07:05 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>
#include <mlx.h>

t_env	*singleton_env(void)
{
	static t_env	env;

	return (&env);
}

void	init_scene(t_scene *scene)
{
	scene->objs = NULL;
	scene->lights = NULL;
}

int		quit(void *param)
{
	(void)param;
	exit(0);
}

void	init_cam(t_scene *scene)
{
	scene->cam.dir.x = 0;
	scene->cam.dir.y = -1;
	scene->cam.dir.z = 0;
	scene->cam.pos.x = 0;
	scene->cam.pos.y = 12;
	scene->cam.pos.z = 0;
}

int		init_env(t_env *env)
{
	env->width = env->scene->width;
	env->height = env->scene->height;
	env->name = env->scene->name;
	env->width_per_height = (float)env->width / (float)env->height;
	env->win = NULL;
	env->img = NULL;
	env->mlx = NULL;
	if (!(env->mlx = mlx_init()))
		fatal("mlx problem");
	if (!(env->win = mlx_new_window(env->mlx, env->width,
	env->height, env->name)))
		fatal("mlx problem");
	if (!(env->img = mlx_new_image(env->mlx, env->width,
	env->height)))
		fatal("mlx problem");
	env->ptr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
	&env->endian);
	return (0);
}
