/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 00:09:30 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <math.h>

float	calc_dist(float t, cl_float3 ray)
{
	cl_float3	cam_to_obj;
	float		dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	return (dist);
}

void	change_repere(t_obj obj, cl_float3 *pos_transformed,\
		cl_float3 *ray_transformed)
{
	float		matrix[3][3];
	float		inverted_matrix[3][3];

	set_rotation_matrix(matrix, obj.dirx, obj.diry, obj.dirz);
	invert_matrix(matrix, inverted_matrix);
	*pos_transformed = mat_mult_vect(inverted_matrix, *pos_transformed);
	*ray_transformed = mat_mult_vect(inverted_matrix, *ray_transformed);
}

int		hit_calc_dist(t_obj obj, cl_float3 pos_transformed,\
		cl_float3 ray_transformed, struct s_result_hit *result_hit)
{
	float		t;
	float		dist;

	t = calc_obj(&obj, pos_transformed, ray_transformed);
	if (t < 0.001)
		t = 0;
	dist = calc_dist(t, ray_transformed);
	if (dist > 0.0001 && dist < result_hit->dist)
	{
		result_hit->dist = dist;
		return (1);
	}
	return (0);
}

int		hit(t_scene *scene, cl_float3 cam_pos, cl_float3 ray,\
		struct s_result_hit *result_hit)
{
	cl_float3	pos_transformed;
	cl_float3	ray_transformed;
	int			i;
	t_obj		obj;
	int			hit;

	i = 0;
	hit = 0;
	result_hit->dist = 10000.0;
	while (i < scene->objs_number)
	{
		obj = scene->objs[i];
		pos_transformed = sub_vect(cam_pos, obj.pos);
		ray_transformed = ray;
		if (obj.type != PLAN && obj.type != SPHERE)
			change_repere(obj, &pos_transformed, &ray_transformed);
		if ((hit = hit_calc_dist(obj, pos_transformed, ray_transformed,\
						result_hit)) == 1)
			result_hit->indice = i;
		i++;
	}
	return (result_hit->dist != 10000.0);
}

int		mouse_event(int button, int x, int y)
{
	cl_float3			ray;
	float				coef;
	t_env				*env;
	struct s_result_hit	result_hit;
	cl_float3			cam_dir;

	if (button == 1)
	{
		env = singleton_env();
		cam_dir = env->scene->cam.dir;
		ray = add_vect(cam_dir, (cl_float3){.x = 0, .y = 0, .z = 0});
		ray = normalize(ray);
		coef = (((float)y - ((float)env->height / 2)) /\
				((float)env->height / 2)) * 0.3;
		ray.z += -coef * env->scene->norm_vert.z;
		coef = (((float)x - ((float)env->width / 2)) /\
				((float)env->width / 2)) * 0.3 * env->width_per_height;
		ray.y -= coef * env->scene->norm_hor.y;
		ray.x -= coef * env->scene->norm_hor.x;
		ray = normalize(ray);
		if (hit(env->scene, env->scene->cam.pos, ray, &result_hit))
			env->indice_obj = result_hit.indice;
	}
	return (1);
}
