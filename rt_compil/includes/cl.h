/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 00:23:16 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 00:27:43 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H
# define CL_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <OpenCL/opencl.h>
# include "rt.h"

struct					s_cl_args
{
	t_obj				*objs;
	cl_mem				objs_buffer;
	size_t				objs_size;

	t_light				*lights;
	cl_mem				lights_buffer;
	size_t				lights_size;
};

struct					s_cl
{
	size_t				global;
	size_t				local;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_kernel			kernel;
	cl_mem				output;
	size_t				data_size;
}						t_cl;

int						cl_init(struct s_cl *cl);
int						file_to_str(char *filename, char **source_str);
int						cl_load_program_from_source(struct s_cl *cl,\
		char **source_str, cl_program *program);
int						cl_create_kernel_from_program(cl_program program,\
		char *func_name, cl_kernel *kernel);
int						cl_create_buffer(struct s_cl *cl, int rights,\
		size_t data_size, cl_mem *output);
int						cl_set_arg(cl_kernel kernel, size_t size,\
		int *i, void *ptr);
int						cl_write_buffer(struct s_cl *cl, cl_mem buffer,\
		void *data, size_t data_size);
int						cl_exec(struct s_cl *cl, size_t global,\
		cl_kernel kernel);
int						cl_read_results(struct s_cl *cl, cl_mem output,\
		size_t output_size, int *result);

#endif
