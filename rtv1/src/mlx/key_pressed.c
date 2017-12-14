/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 00:09:30 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

int		ft_key_pressed_rot(int keycode, t_env *cast)
{
	if (keycode == KEY_4)
		cast->rotx = 1;
	if (keycode == KEY_7)
		cast->rotx = -1;
	if (keycode == KEY_5)
		cast->roty = 1;
	if (keycode == KEY_8)
		cast->roty = -1;
	if (keycode == KEY_6)
		cast->rotz = 1;
	if (keycode == KEY_9)
		cast->rotz = -1;
	if (keycode == KEY_R)
		cast->key_r = 1;
	if (keycode == KEY_T)
		cast->key_t = 1;
	return (0);
}

int		ft_key_pressed(int keycode, void *env)
{
	t_env	*cast;

	cast = (t_env *)env;
	if (keycode == 13)
		cast->rot_right = 1;
	if (keycode == KEY_SHIFT_LEFT)
		cast->key_shift_left = 1;
	if (keycode == KEY_SHIFT_RIGHT)
		cast->key_shift_right = 1;
	if (keycode == KEY_UP)
		cast->up = 1;
	if (keycode == KEY_DOWN)
		cast->down = 1;
	if (keycode == KEY_SPACE)
		cast->forward = 1;
	if (keycode == KEY_B)
		cast->backward = 1;
	if (keycode == KEY_RIGHT)
		cast->right = 1;
	if (keycode == KEY_LEFT)
		cast->left = 1;
	if (keycode == KEY_ESCAPE)
		exit(0);
	ft_key_pressed_rot(keycode, cast);
	return (0);
}

int		ft_key_release_rot(int keycode, t_env *cast)
{
	if (keycode == KEY_R)
		cast->key_r = 0;
	if (keycode == KEY_T)
		cast->key_t = 0;
	if (keycode == KEY_4)
		cast->rotx = 0;
	if (keycode == KEY_7)
		cast->rotx = 0;
	if (keycode == KEY_5)
		cast->roty = 0;
	if (keycode == KEY_8)
		cast->roty = 0;
	if (keycode == KEY_6)
		cast->rotz = 0;
	if (keycode == KEY_9)
		cast->rotz = 0;
	return (0);
}

int		ft_key_release(int keycode, void *env)
{
	t_env	*cast;

	cast = (t_env *)env;
	if (keycode == 14)
		cast->rot_left = 1;
	if (keycode == KEY_UP)
		cast->up = 0;
	if (keycode == KEY_DOWN)
		cast->down = 0;
	if (keycode == KEY_SPACE)
		cast->forward = 0;
	if (keycode == KEY_B)
		cast->backward = 0;
	if (keycode == KEY_RIGHT)
		cast->right = 0;
	if (keycode == KEY_LEFT)
		cast->left = 0;
	if (keycode == KEY_SHIFT_LEFT)
		cast->key_shift_left = 0;
	if (keycode == KEY_SHIFT_RIGHT)
		cast->key_shift_right = 0;
	ft_key_release_rot(keycode, cast);
	return (0);
}
