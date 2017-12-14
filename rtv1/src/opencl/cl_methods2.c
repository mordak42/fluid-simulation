/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_methods2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 00:32:57 by vcombey          ###   ########.fr       */
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

int		cl_create_buffer(struct s_cl *cl, int rights, size_t data_size,\
		cl_mem *output)
{
	*output = clCreateBuffer(cl->context, rights, data_size, NULL, NULL);
	if (!output)
	{
		ft_putstr_fd("Error: Failed to allocate device memory!\n", 2);
		exit(1);
	}
	return (EXIT_SUCCESS);
}

int		cl_write_buffer(struct s_cl *cl, cl_mem buffer, void *data,\
		size_t data_size)
{
	int	err;

	err = 0;
	clEnqueueWriteBuffer(cl->commands, buffer, CL_TRUE, 0, data_size, data, 0,\
			NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putstr_fd("Error: Failed to write to source array!\n", 2);
		exit(1);
	}
	return (EXIT_SUCCESS);
}

int		cl_set_arg(cl_kernel kernel, size_t size, int *i, void *ptr)
{
	int	err;

	if (ptr == NULL)
		ft_putstr_fd("ptr is null\n", 2);
	err = 0;
	err = clSetKernelArg(kernel, *i, size, ptr);
	(*i)++;
	if (err != CL_SUCCESS)
	{
		ft_putstr_fd("Error: Failed to set kernel arguments! %d\n", 2);
		exit(1);
	}
	return (EXIT_SUCCESS);
}

int		cl_exec(struct s_cl *cl, size_t global, cl_kernel kernel)
{
	int	err;

	err = 0;
	err = clGetKernelWorkGroupInfo(kernel, cl->device_id,\
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local), &cl->local, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putstr_fd("Error: Failed to retrieve kernel work group info! \n", 2);
		exit(1);
	}
	err = clEnqueueNDRangeKernel(cl->commands, kernel, 1, NULL, &global,\
			&cl->local, 0, NULL, NULL);
	if (err)
	{
		ft_putstr_fd("Error: Failed to execute kernel!\n", 2);
		exit(1);
	}
	clFinish(cl->commands);
	return (EXIT_SUCCESS);
}

int		cl_read_results(struct s_cl *cl, cl_mem output, size_t output_size,\
		int *result)
{
	int	err;

	err = 0;
	err = clEnqueueReadBuffer(cl->commands, output, CL_TRUE, 0, output_size,\
			result, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putstr_fd("Error: Failed to read output array! \n", 2);
		exit(1);
	}
	return (EXIT_SUCCESS);
}
