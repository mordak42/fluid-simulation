/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 21:30:35 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 23:23:47 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenCL/opencl.h>
#include <mlx.h>
#include "mlx.h"
#include "rt.h"
#include "libft.h"
#include "cl.h"

void	calc_scene_set_arg(struct s_cl *cl, struct s_cl_args *cl_args,\
		t_env *env)
{
	int			i;

	i = 0;
	cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl->output);
	cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl_args->objs_buffer);
	cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl_args->lights_buffer);
	cl_set_arg(cl->kernel, sizeof(int), &i, &env->height);
	cl_set_arg(cl->kernel, sizeof(int), &i, &env->width);
	cl_set_arg(cl->kernel, sizeof(float), &i, &env->width_per_height);
	cl_set_arg(cl->kernel, sizeof(int), &i, &env->scene->objs_number);
	cl_set_arg(cl->kernel, sizeof(int), &i, &env->scene->lights_number);
	cl_set_arg(cl->kernel, sizeof(cl_float3), &i, &env->scene->cam.dir);
	cl_set_arg(cl->kernel, sizeof(cl_float3), &i, &env->scene->cam.pos);
	cl_set_arg(cl->kernel, sizeof(cl_float3), &i, &env->scene->norm_hor);
	cl_set_arg(cl->kernel, sizeof(cl_float3), &i, &env->scene->norm_vert);
}

int		calc_scene(struct s_cl *cl, struct s_cl_args *cl_args, t_env *env)
{
	cl_program	program;
	char		*source_str;

	cl->data_size = env->width * env->height * sizeof(int);
	cl_init(cl);
	file_to_str("./built.c", &source_str);
	cl_load_program_from_source(cl, &source_str, &program);
	free(source_str);
	cl_create_kernel_from_program(program, "calc", &cl->kernel);
	cl_create_buffer(cl, CL_MEM_WRITE_ONLY, cl->data_size, &cl->output);
	cl_create_buffer(cl, CL_MEM_READ_ONLY, cl_args->objs_size,\
				&cl_args->objs_buffer);
	cl_create_buffer(cl, CL_MEM_READ_ONLY, cl_args->lights_size,\
				&cl_args->lights_buffer);
	cl_write_buffer(cl, cl_args->lights_buffer, cl_args->lights,\
				cl_args->lights_size);
	cl_write_buffer(cl, cl_args->objs_buffer, cl_args->objs,\
				cl_args->objs_size);
	calc_scene_set_arg(cl, cl_args, env);
	cl_exec(cl, env->width * env->height, cl->kernel);
	cl_read_results(cl, cl->output, cl->data_size, (int *)env->ptr);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (EXIT_SUCCESS);
}

int		recalc_scene(t_env *env)
{
	struct s_cl			*cl;
	struct s_cl_args	*cl_args;
	int					i;

	i = 0;
	cl = env->cl;
	cl_args = env->cl_args;
	recalc_img(env->scene);
	if (env->obj_has_changed)
	{
		env->obj_has_changed = 0;
		cl_write_buffer(cl, cl_args->objs_buffer, cl_args->objs,\
					cl_args->objs_size);
	}
	calc_scene_set_arg(cl, cl_args, env);
	if (cl_exec(cl, env->width * env->height, cl->kernel))
		exit(1);
	ft_memset(env->ptr, 0x00, env->width * env->height * 4);
	if (cl_read_results(cl, cl->output, cl->data_size, (int *)env->ptr))
		exit(1);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (EXIT_SUCCESS);
}

void	mlx(t_env *env)
{
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, &ft_key_pressed, env);
	mlx_hook(env->win, KEYRELEA, KEYRELEAMASK, &ft_key_release, env);
	mlx_loop_hook(env->mlx, recalc_scene, env);
	mlx_hook(env->win, 17, 1, &quit, NULL);
	mlx_mouse_hook(env->win, &mouse_event, NULL);
	mlx_loop(env->mlx);
}

int		main(int ac, char **av)
{
	t_env				*env;
	t_scene				scene;
	struct s_cl			cl;
	struct s_cl_args	cl_args;

	if (ac != 2)
		fatal("usage: rt_v1 <filename>");
	init_scene(&scene);
	env = singleton_env();
	parse_file(av[1], &scene);
	ft_bzero(&cl, sizeof(struct s_cl));
	ft_bzero(&cl_args, sizeof(struct s_cl));
	env->cl = &cl;
	env->scene = &scene;
	init_env(env);
	cl_args.objs = scene.objs;
	cl_args.lights = scene.lights;
	cl_args.objs_size = scene.objs_number * (sizeof(t_obj) + 1);
	cl_args.lights_size = scene.lights_number * (sizeof(t_light) + 1);
	env->cl_args = &cl_args;
	recalc_img(env->scene);
	init_norm_cam_dir(&scene.norm_vert, &scene.norm_hor, scene.cam.dir);
	calc_scene(&cl, &cl_args, env);
//    sleep(100);
 //   exit (1);
	mlx(env);
	return (0);
}
