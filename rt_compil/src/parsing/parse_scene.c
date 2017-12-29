/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 23:00:19 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

static	t_func	g_scene_func[] =
{
	{"name", &get_name},
	{"camera", &get_camera},
	{"windows_size", &get_windows_size},
	{"object", &get_all_objects},
	{"light", &get_light},
	{NULL, NULL},
};

size_t	get_name(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	(void)len;
	if (!lines[i].value[0])
		fatal("bad name");
	scene->name = ft_strdup(lines[i].value);
	return (i + 1);
}

size_t	get_windows_size(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	char	*coord;

	(void)len;
	if (!lines[i].value[0])
		fatal("bad windows size");
	coord = lines[i].value;
	if (!(ft_atoi_safe(coord, &coord, (int *)&scene->width)))
		fatal("bad windows size");
	if (!(ft_atoi_safe(coord, &coord, (int *)&scene->height)))
		fatal("bad windows size");
	if (scene->height > 1440 || scene->width > 2560)
		fatal("windows size too big");
	if (!ft_str_is_clear(coord))
		fatal("bad windows size");
	return (i + 1);
}

size_t	get_camera(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	int		vecteur;
	int		origin;

	vecteur = 0;
	origin = 0;
	(void)len;
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("bad camera");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		if (ft_strequ(lines[i].key, "vecteur") && ++vecteur)
			scene->cam.dir = get_coordinates(scene->cam.dir, lines[i].value);
		if (ft_strequ(lines[i].key, "origin") && ++origin)
			scene->cam.pos = get_coordinates(scene->cam.pos, lines[i].value);
		i++;
	}
	if (!(vecteur && origin))
		fatal("bad vecteur or origin specified for the camera");
	return (i);
}

void	parse_scene(t_yaml *lines, size_t len, t_scene *scene)
{
	size_t		i;
	size_t		k;

	if (len == 0 || len == 1)
		fatal("to short file");
	i = 0;
	if (!ft_strequ(lines[0].key, "scene"))
		fatal("need scene");
	i++;
	ft_bzero(scene, sizeof(t_scene));
	scene->lights = ft_memalloc(sizeof(t_light) * 15);
	while (i < len)
	{
		k = 0;
		while (g_scene_func[k].key && !ft_strequ(g_scene_func[k].key,\
					lines[i].key))
			k++;
		if (g_scene_func[k].f == NULL)
			fatal("bad scene content");
		i = g_scene_func[k].f(lines, i, scene, len);
	}
	if (!scene->name)
		fatal("no scene name specified");
	if (scene->height == 0 || scene->width == 0)
		fatal("bad screen format");
}
