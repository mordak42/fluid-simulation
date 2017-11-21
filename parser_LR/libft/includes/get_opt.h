#ifndef GET_OPT_H
# define GET_OPT_H
# include <stdlib.h>
# include <stdio.h>

# define OPTION_BOOL 0
# define OPTION_STRING 1

typedef struct		s_option
{
	int			id;
	char		*name;
	int			type;
	char		*fill;
	char		*desc;

}					t_option;

typedef struct		s_programinfo
{
	char		*progname;
	char		*desc;
	t_option	*list_option;
	const char		**argv;
	int			argc;
	int			argparg;
	int			argcur;
	int			argpos;
	const char		*argopt;
	int			argerr;
	int			min;
}					t_programinfo;

void				opt_init(t_programinfo *pi, int argc, const char **argv);
t_option			*get_opt_by_id(t_programinfo *pi, int id);
int					get_opt(t_programinfo *pi);
void				display_bool(t_programinfo *pi);
void				display_string(t_programinfo *pi);
void				display_desc(t_programinfo *pi);
void				get_opt_display_usage(t_programinfo *pi);
void				get_opt_display_error(t_programinfo *pi, int id);
#endif
