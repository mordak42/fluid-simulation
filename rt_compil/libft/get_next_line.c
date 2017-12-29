/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 21:36:40 by vcombey           #+#    #+#             */
/*   Updated: 2017/01/04 19:03:34 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

char		*ft_strdupn(const char *s, size_t n)
{
	char	*dst;

	dst = (char *)malloc((n + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_strncpy(dst, s, n);
	dst[n] = 0;
	return (dst);
}

int			grow_buffer(const int fd, char **original_buffer)
{
	char	tmp[BUFF_SIZE + 1];
	char	*new_buffer;
	int		ret;

	ret = read(fd, tmp, BUFF_SIZE);
	if (ret > 0)
	{
		tmp[ret] = '\0';
		new_buffer = ft_strjoin(*original_buffer, tmp);
		free(*original_buffer);
		*original_buffer = new_buffer;
	}
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	char		*tmp;
	static char	*buf = NULL;
	int			ret;

	ret = 1;
	if (buf == NULL && (buf = ft_strnew(0)) == NULL)
		return (-1);
	while (ret > 0)
	{
		if ((tmp = ft_strchr(buf, '\n')) != NULL)
		{
			*line = ft_strdupn(buf, tmp - buf);
			*tmp = '\0';
			ft_memmove(buf, tmp + 1, ft_strlen(tmp + 1) + 1);
			return (1);
		}
		ret = grow_buffer(fd, &buf);
	}
	if (*buf != '\0')
	{
		*line = ft_strdup(buf);
		*buf = '\0';
		return (1);
	}
	return (0);
}
