/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/27 00:08:51 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include "libft.h"

void	parse_line(char *line, t_yaml *new)
{
	size_t	tab;
	char	*sep;
	char	*comment;

	tab = 0;
	while (*line && *line == '\t')
	{
		tab++;
		line++;
	}
	new->tab = tab;
	if ((comment = ft_strchr(line, '#')))
		*comment = '\0';
	if (!(sep = ft_strchr(line, ':')))
		fatal("bad yaml");
	if (ft_strchr(sep + 1, ':'))
		fatal("bad yaml");
	*sep = '\0';
	new->key = ft_strtrim(line);
	new->value = ft_strtrim(sep + 1);
}

void	valid_yaml(t_yaml *lines, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len && i + 1 < len)
	{
		if (lines[i].value[0] && (lines[i].tab < lines[i + 1].tab))
			fatal("bad yaml");
		if (!lines[i].value[0] && lines[i].tab + 1 != lines[i + 1].tab)
			fatal("bad yaml");
		i++;
	}
}

void	free_yaml(t_yaml *lines, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(lines[i].value);
		free(lines[i].key);
		i++;
	}
}

void	parse_file(char *filename, t_scene *scene)
{
	int		fd;
	t_yaml	*lines;
	char	*line;
	size_t	i;

	if (!(lines = ft_memalloc(sizeof(t_yaml) * 100)))
		exit(1);
	if ((fd = open(filename, O_RDONLY)) == -1)
		fatal("error");
	i = 0;
	while (get_next_line(fd, &line))
	{
		parse_line(line, lines + i);
		free(line);
		if (i > 998)
			fatal("file too large, fuck you");
		i++;
	}
	close(fd);
	valid_yaml(lines, i);
	parse_scene(lines, i, scene);
	free_yaml(lines, i);
	free(lines);
}
