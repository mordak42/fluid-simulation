/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 19:14:45 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

size_t	get_light(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_light	*new_light;

	(void)len;
	new_light = &scene->lights[scene->lights_number];
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("bad light");
	i++;
	if (ft_strequ(lines[i].key, "origin"))
		new_light->pos = get_coordinates(new_light->pos, lines[i].value);
	else
		fatal("bad light propriety");
	i++;
	scene->lights_number++;
	return (i);
}
