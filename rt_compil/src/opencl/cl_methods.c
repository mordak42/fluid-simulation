/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_methods.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 23:01:27 by vcombey          ###   ########.fr       */
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
#include "libft.h"
#include "cl.h"
#include "rt.h"

int		cl_init(struct s_cl *cl)
{
	int err;

	err = 0;
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device_id, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putstr_fd("Error: Failed to create a device group!\n", 2);
		exit(1);
	}
	cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &err);
	if (!cl->context)
	{
		ft_putstr_fd("Error: Failed to create a compute context!\n", 2);
		exit(1);
	}
	cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	if (!cl->commands)
	{
		ft_putstr_fd("Error: Failed to create a command commands!\n", 2);
		exit(1);
	}
	return (EXIT_SUCCESS);
}

int		file_to_str(char *filename, char **source_str)
{
	size_t	max_source_size;
	int		fd;
	size_t	source_size;

	max_source_size = 50000;
	fd = open(filename, O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("open failed.\n", 2);
		exit(1);
	}
	*source_str = ft_strnew(max_source_size);
	source_size = read(fd, *source_str, max_source_size);
	if (source_size == 0)
	{
		ft_putstr_fd("read failed.\n", 2);
		exit(1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int		cl_load_program_from_source(struct s_cl *cl, char **source_str,\
		cl_program *program)
{
	int		err;
	size_t	len;
	char	buffer[5000000];

	err = 0;
	*program = clCreateProgramWithSource(cl->context, 1, (const char **)\
			source_str, NULL, &err);
	if (err || !*program)
	{
		ft_putstr_fd("Error: Failed to create compute program!\n", 2);
		exit(1);
	}
	err = clBuildProgram(*program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putstr_fd("Error: Failed to build program executable!\n", 2);
		clGetProgramBuildInfo(*program, cl->device_id, CL_PROGRAM_BUILD_LOG,\
				sizeof(buffer), buffer, &len);
		ft_putstr_fd(buffer, 2);
		exit(1);
	}
	return (EXIT_SUCCESS);
}

int		cl_create_kernel_from_program(cl_program program, char *func_name,\
		cl_kernel *kernel)
{
	int	err;

	err = 0;
	*kernel = clCreateKernel(program, func_name, &err);
	if (!*kernel || err != CL_SUCCESS)
	{
		ft_putstr_fd("Error: Failed to create compute kernel! \n", 2);
		exit(1);
	}
	return (EXIT_SUCCESS);
}
