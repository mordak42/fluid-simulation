/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:21:43 by tcanaud           #+#    #+#             */
/*   Updated: 2017/11/12 16:55:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_opt.h>
#include <libft.h>

void			opt_init(t_programinfo *pi, int argc, const char **argv)
{
	pi->argc = argc;
	pi->argv = argv;
}

static int		get_opt_arg(t_programinfo *pi, t_option *opt)
{
	if (opt->type == OPTION_BOOL)
		return (opt->id);
	if ((ft_strlen(opt->name) == 1) && (pi->argparg <= pi->argcur))
		pi->argparg = pi->argcur + 1;
	if (pi->argparg <= pi->argcur)
		pi->argparg = pi->argcur;
	if (pi->argparg != pi->argc)
	{
		pi->argopt = pi->argv[pi->argparg];
		pi->argparg += 1;
	}
	else
		pi->argerr = 1;
	return (opt->id);
}

static int		get_opt_by_name(t_programinfo *pi, const char *str)
{
	size_t		slen;
	int			longopt;
	t_option	*opt;
	size_t		optlen;

	slen = ft_strlen(str);
	longopt = 0;
	opt = pi->list_option;
	if ((pi->argpos == 0) && (slen > 2) && (ft_memcmp(str, "--", 2) == 0))
		longopt = 1;
	if ((pi->argpos == 0) && (longopt == 1) && (pi->argpos += 2))
		slen = ft_strlen((str += 2));
	else if ((pi->argpos == 0) && (pi->argpos += 1))
		slen = ft_strlen((str += 1));
	while ((opt->name != NULL) && (optlen = ft_strlen(opt->name)))
	{
		if (((longopt == 0) && (ft_memcmp(str, opt->name, 1) == 0)
					&& (pi->argpos += 1)) || ((longopt == 1) && (optlen == slen)
					&& (ft_memcmp(str, opt->name, slen) == 0) &&
					!(pi->argpos = 0) && (pi->argcur += 1)))
			return (get_opt_arg(pi, opt));
		++opt;
	}
	return ((pi->argerr = 1) - 2);
}

t_option		*get_opt_by_id(t_programinfo *pi, int id)
{
	t_option	*opt;

	opt = pi->list_option;
	while ((opt->name != NULL) && (opt->id != id))
		++opt;
	if (opt->id == id)
		return (opt);
	return (NULL);
}

int				get_opt(t_programinfo *pi)
{
	const char	*str;

	pi->argopt = NULL;
	if ((pi->argv[pi->argcur] != NULL) &&
			((pi->argv[pi->argcur][pi->argpos] == '\0')
			|| (pi->argpos == 0)) && (pi->argcur < pi->argparg))
	{
		pi->argcur = pi->argparg;
		pi->argpos = 0;
	}
	if ((pi->argv[pi->argcur] != NULL) && (pi->argpos != 0)
			&& (pi->argv[pi->argcur][pi->argpos] == '\0')
			&& !(pi->argpos = 0))
		pi->argcur += 1;
	if (pi->argv[pi->argcur] == NULL)
		return (0);
	str = &pi->argv[pi->argcur][pi->argpos];
	if ((pi->argpos == 0) && ((str[0] != '-') && (str[0] != '+')))
		return (-1);
	else if ((pi->argpos == 0) && (ft_strlen(str) == 2)
			&& (ft_memcmp(str, "--", 2) == 0) && (pi->argcur += 1))
		return (0);
	if (pi->argpos == 0)
		pi->min = str[0];
	return (get_opt_by_name(pi, str));
}
