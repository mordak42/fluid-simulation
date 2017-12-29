/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 00:22:28 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 00:30:37 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCT_H
# define RT_STRUCT_H

typedef struct			s_point
{
	float				x;
	float				y;
	float				z;
}						t_point;

typedef struct			s_cam
{
	cl_float3			dir;
	cl_float3			pos;
}						t_cam;

typedef struct			s_obj
{
	int					type;
	cl_float3			pos;
	cl_float3			dirx;
	cl_float3			diry;
	cl_float3			dirz;
	size_t				color;
	float				alpha;
	float				rayon;
}						t_obj;

typedef struct			s_light
{
	cl_float3			pos;
}						t_light;

typedef struct			s_yaml
{
	size_t				tab;
	char				*key;
	char				*value;
}						t_yaml;

typedef struct			s_scene
{
	char				*name;
	cl_float3			rot;
	size_t				width;
	size_t				height;
	t_cam				cam;
	cl_float3			norm_hor;
	cl_float3			norm_vert;
	t_obj				*objs;
	int					objs_number;
	t_light				*lights;
	int					lights_number;
}						t_scene;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	int					width;
	int					height;
	size_t				up;
	size_t				down;
	size_t				forward;
	size_t				backward;
	size_t				right;
	size_t				left;
	size_t				key_shift_left;
	size_t				key_shift_right;
	size_t				key_r;
	size_t				key_t;
	size_t				rot_right;
	size_t				rot_left;
	float				width_per_height;
	char				*ptr;
	int					bpp;
	int					size_line;
	int					endian;
	char				*name;
	struct s_cl			*cl;
	struct s_cl_args	*cl_args;
	t_scene				*scene;
	int					mouse_x;
	int					mouse_y;
	int					rotx;
	int					roty;
	int					rotz;
	int					indice_obj;
	int					obj_has_changed;
}						t_env;

struct					s_result_hit
{
	float				dist;
	float				t;
	int					indice;
	cl_float3			norm;
	cl_float3			intersect;
	t_obj				obj;
};

typedef struct			s_func
{
	char				*key;
	size_t				(*f)(t_yaml *, size_t, t_scene *k, size_t);
}						t_func;

#endif
