/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 00:17:20 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 23:00:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <string.h>
# include <mlx.h>
# include <OpenCL/opencl.h>
# include "rt_struct.h"
# define TETA_ROT 0.1
# define TETA 0.02

# define SPHERE 0
# define CONE 1
# define PLAN 2
# define CYLINDRE 3

# define KEY_ESCAPE 53
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_B 11
# define KEY_SPACE 49
# define KEY_PAD_SUB 78
# define KEY_PAD_ADD 69
# define KEY_R 15
# define KEY_Z 6
# define KEY_H 4
# define KEY_S 1
# define KEY_SHIFT_LEFT 257
# define KEY_SHIFT_RIGHT 258
# define KEY_R 15
# define KEY_T 17
# define KEYPRESSMASK (1l << 0)
# define KEYRELEAMASK (1l << 1)
# define KEYPRESS 2
# define KEYRELEA 3
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 800
# define WIDTH_PER_HEIGHT SCREEN_WIDTH/SCREEN_HEIGHT
# define KEY_7 89
# define KEY_4 86
# define KEY_8 91
# define KEY_5 87
# define KEY_9 92
# define KEY_6 88

t_env		*env(void);
int			init_env(t_env *env);
void		calc(t_env *env, t_scene *scene);
void		ft_pixelput(t_env *env, int x, int y, int color);
void		parse_file(char *filename, t_scene *scene);
void		debug_scene(t_scene *scene);
cl_float3	get_coordinates(cl_float3	res, char *value);
void		parse_scene(t_yaml *lines, size_t len, t_scene *scene);
size_t		get_name(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t		get_windows_size(t_yaml *lines, size_t i, t_scene *scene,\
		size_t len);
size_t		get_camera(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t		get_all_objects(t_yaml *lines, size_t i, t_scene *scene,\
		size_t len);
size_t		get_cone(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t		get_cylindre(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t		get_plan(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t		get_sphere(t_yaml *lines, size_t i, t_scene *scene, size_t len);
void		ft_obj_add(t_obj *new_node, t_obj **first);
double		get_rayon(char *value);
size_t		get_hexa(char *value);
void		ft_obj_add(t_obj *new_node, t_obj **first);
t_obj		*ft_new_obj(void);
void		assign_obj_func(t_scene *scene);
size_t		get_light(t_yaml *lines, size_t i, t_scene *scene, size_t len);
int			ft_key_pressed(int keycode, void *env);
int			ft_key_release(int keycode, void *env);
t_env		*singleton_env();
int			recalc_img(void *scene);
void		init_scene(t_scene *scene);
int			quit(void *param);
void		init_norm_cam_dir(cl_float3 *norm_vert, cl_float3 *norm_hor,\
		cl_float3 dir);
int			mouse_event(int button, int x, int y);
float		calc_obj(t_obj *obj, cl_float3 pos, cl_float3 ray);
float		ft_min(float u, float v);
float		ft_abs_float(float u);
float		norme_carre(cl_float3 v);
float		scalar_product(cl_float3 u, cl_float3 v);
cl_float3	normalize(cl_float3 v);
cl_float3	mult_vect(cl_float3 v, float t);
cl_float3	div_vect(cl_float3 v, float t);
cl_float3	add_vect(cl_float3 u, cl_float3 v);
cl_float3	cpy_vect(cl_float3 u, cl_float3 v);
cl_float3	sub_vect(cl_float3 u, cl_float3 v);
cl_float3	vectorial_product(cl_float3 u, cl_float3 v);
cl_float3	rot(cl_float3 v, float teta);
float		calc_delta(float a, float b, float c);
cl_float3	rot_x(cl_float3 v, float teta);
cl_float3	rot_y(cl_float3 v, float teta);
cl_float3	rot_z(cl_float3 v, float teta);
void		set_rotation_matrix(float m[3][3], cl_float3 vx, cl_float3 vy,\
		cl_float3 vz);
int			invert_matrix(float m[3][3], float inv_m[3][3]);
cl_float3	mat_mult_vect(float a[3][3], cl_float3 v);
float		ft_min_positiv(float a, float b);
cl_float3	rodrigues(cl_float3 input, cl_float3 v, float teta);
void		move_arows(t_env *env, t_scene *s);
void		get_vecteur(t_obj *new, char *line);
void		rot_obj(t_env *env, t_scene *s,\
		cl_float3 (f_rot)(cl_float3, float), int sign_rot);
int			ft_str_is_clear(char *str);
#endif
