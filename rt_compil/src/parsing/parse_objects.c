/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 19:18:07 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "libft.h"

static	t_func	g_scene_func[] =
{
	{"sphere", &get_sphere},
	{"plan", &get_plan},
	{"cone", &get_cone},
	{"cylindre", &get_cylindre},
	{NULL, NULL},
};

size_t	get_sphere(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	new = &scene->objs[scene->objs_number];
	new->type = SPHERE;
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		if (ft_strequ(lines[i].key, "origin"))
			new->pos = get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "vecteur"))
			new->dirz = get_coordinates(new->dirz, lines[i].value);
		else if (ft_strequ(lines[i].key, "rayon"))
			new->rayon = get_rayon(lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	return (i);
}

size_t	get_plan(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	new = &scene->objs[scene->objs_number];
	new->type = PLAN;
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		if (ft_strequ(lines[i].key, "origin"))
			new->pos = get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "vecteur"))
			new->dirz = get_coordinates(new->dirz, lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	return (i);
}

size_t	get_cylindre(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	new = &scene->objs[scene->objs_number];
	new->type = CYLINDRE;
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		if (ft_strequ(lines[i].key, "origin"))
			new->pos = get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "vecteur"))
			get_vecteur(new, lines[i].value);
		else if (ft_strequ(lines[i].key, "rayon"))
			new->rayon = get_rayon(lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	return (i);
}

size_t	get_cone(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	new = &scene->objs[scene->objs_number];
	new->type = CONE;
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		if (ft_strequ(lines[i].key, "origin"))
			new->pos = get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "vecteur"))
			get_vecteur(new, lines[i].value);
		else if (ft_strequ(lines[i].key, "alpha"))
			new->alpha = get_rayon(lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	return (i);
}

size_t	get_all_objects(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t		k;
	size_t		tab;

	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("invalid objects value");
	scene->objs = ft_memalloc(sizeof(t_obj) * 15);
	scene->objs_number = 0;
	i++;
	while (i < len && lines[i].tab == tab + 1 && scene->objs_number < 15)
	{
		k = 0;
		while (g_scene_func[k].key && !ft_strequ(g_scene_func[k].key,\
					lines[i].key))
			k++;
		if (g_scene_func[k].f == NULL)
			fatal("invalid object name");
		if (lines[i].value[0])
			fatal("object has bad value");
		i = g_scene_func[k].f(lines, i, scene, len);
		scene->objs_number++;
	}
	return (i);
}
