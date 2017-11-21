/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:56:48 by tcanaud           #+#    #+#             */
/*   Updated: 2017/11/12 16:46:12 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_opt.h>
#include <libft.h>

void	display_bool(t_programinfo *pi)
{
	t_option	*opt;
	int			bl;

	opt = pi->list_option;
	bl = 0;
	while (opt->name != NULL)
	{
		if (opt->type == OPTION_BOOL)
		{
			if (bl == 0)
				printf("[-%s", opt->name);
			else
				printf("%s", opt->name);
			bl = 1;
		}
		++opt;
	}
	if (bl)
		printf("]");
}

void	display_string(t_programinfo *pi)
{
	t_option	*opt;

	opt = pi->list_option;
	while (opt->name != NULL)
	{
		if (opt->type == OPTION_STRING)
			printf(" [%.*s%s %s]", (ft_strlen(opt->name) > 1) ? 2 : 1, "--",
					opt->name, opt->fill);
		++opt;
	}
}

void	display_desc(t_programinfo *pi)
{
	t_option	*opt;

	opt = pi->list_option;
	while (opt->name != NULL)
	{
		printf(" %.*s%s %s	 %s\n", (ft_strlen(opt->name) > 1) ? 2 : 1, "--",
				opt->name, opt->fill, opt->desc);
		++opt;
	}
	printf("\n%s\n\n", pi->desc);
}

void	get_opt_display_usage(t_programinfo *pi)
{
	printf("Usage: %s ", pi->progname);
	display_bool(pi);
	display_string(pi);
	printf("\n");
	display_desc(pi);
}

void	get_opt_display_error(t_programinfo *pi, int id)
{
	t_option	*opt;

	if (id < 0)
	{
		printf("%s: illegal option -- %s\n", pi->progname,
				&pi->argv[pi->argcur][pi->argpos]);
	}
	else
	{
		opt = get_opt_by_id(pi, id);
		if (opt == NULL)
			return ;
		printf("%s: %.*s%s: requires additionnal arguments\n", pi->progname,
				(ft_strlen(opt->name) > 1) ? 2 : 1, "--", opt->name);
	}
	get_opt_display_usage(pi);
}
