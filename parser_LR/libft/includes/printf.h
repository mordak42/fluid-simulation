#ifndef PRINTF_H
# define PRINTF_H
# include <string.h>
# include <stdarg.h>
# define P_BUFF_SIZE 4097
# define P_ARG_SIZE 2049

/*
**	Setting up a few macros:
**	- P_ISLENMOD(c) returns 1 if char c is a valid lenght modifier.
**	- P_ISOPT(c) returns 1 if char c is a valid printf option.
**	- P_ISVALID(c) returns 1 if car c is either a len modifier or a valid
**		option.
**	- P_ISCONV(c) returns 1 if char c is a valid conversion specifier.
*/

# define P_ISLENMOD(c) (c == 'l' || c == 'h' || c == 'j' || c == 'z')
# define P_ISOPT(c) (c == '-' ||  c == '+' || c == '#' || c == ' ' || c == '0')
# define P_ISFW(c) (c == '*' || ft_isdigit(c))
# define P_ISPREC(c) (c == '*' || c == '.' || ft_isdigit(c))
# define P_ISVALID(c) (P_ISLENMOD(c) || P_ISOPT(c) || P_ISPREC(c) || P_ISFW(c))

/*
**	The following structure should contain the parsed infos when formating an
**	argument. It should be suitable to use with every printf functions, wether
**	it uses buffers, malloc, or not.
*/

typedef struct	s_printf_info
{
	int			p_lenmod;
	int			p_prec;
	int			p_opt;
	int			p_fieldwidth;
	char		p_convtype;
}				t_pinfo;

/*
**	Defining a few mask for options such as ' ' or '#' or '+'
*/

# define _P_PLUS (0b1)
# define _P_SHARP (0b10)
# define _P_ZERO (0b100)
# define _P_SPACE (0b1000)
# define _P_MINUS (0b10000)

/*
**	Corresponding macros.
*/

# define P_PLUS(x) (x & _P_PLUS)
# define P_SHARP(x) (x & _P_SHARP)
# define P_ZERO(x) (x & _P_ZERO)
# define P_SPACE(x) (x & _P_SPACE)
# define P_MINUS(x) (x & _P_MINUS)

/*
**	Defining masks for lenmod.
*/

# define _P_HMOD (0b1)
# define _P_HHMOD (0b10)
# define _P_LMOD (0b100)
# define _P_LLMOD (0b1000)
# define _P_JMOD (0b10000);
# define _P_ZMOD (0b100000);

/*
**	Corresponding check macros.
*/

# define P_HMOD(x) (x & _P_HMOD)
# define P_HHMOD(x) (x & _P_HHMOD)
# define P_LMOD(x) (x & _P_LMOD)
# define P_LLMOD(x) (x & _P_LLMOD)
# define P_JMOD(x) (x & _P_JMOD)
# define P_ZMOD(x) (x & _P_ZMOD)

/*
**	The printf struct used by the printf allocating buffers.
*/

typedef	struct	s_printf_allocated_buff
{
	char		*buf;
	size_t		buf_size;
	size_t		buf_index;
}				t_pab;

/*
**	The structure allowing us to redirect to the right conversion function and
**	the right stdarg argument..
*/
typedef struct	s_printf_conv
{
	char		key;
	int			(*f)(t_pinfo, t_pab*, va_list);
}				t_pconv;

/*
**	In file printf.c
*/

int				ft_printf(const char *format, ...);

/*
**	In file sprintf.c
*/

int				ft_sprintf(char *str, const char *format, ...);

/*
**	In file dprintf.c
*/

int				ft_dprintf(int fd, const char *format, ...);

/*
**	In file asprintf.c
*/

int				ft_asprintf(char **str, const char *format, ...);

/*
**	In file vasprintf.c
*/

int				ft_vasprintf(char **buffer, const char *format, va_list ap);

/*
**	In file buff_loop.c
*/

int				buff_loop(const char *format, char **str, va_list ap);

/*
**	In file buff_start_conv.c
*/

int				p_realloc_buffer(t_pab *s_buf);
int				buff_start_conv(const char *format, size_t *format_index, \
		t_pab *s_buf, va_list ap);

/*
**	In file printf_parse.c
*/

t_pinfo			printf_parse(const char *format, size_t	\
		*format_index, va_list ap);

/*
**	In file s_conv.c
*/

int				p_sconv(t_pinfo pinfo, t_pab *buf, va_list ap);

/*
**	in file d_conv.c
*/

int				p_prec(t_pab *s_buf, size_t len, t_pinfo pinfo);
int				p_padd(t_pab *s_buf, size_t len, t_pinfo pinfo);
int				p_dconv(t_pinfo pinfo, t_pab *buf, va_list ap);

/*
**	in file c_conv.c
*/

int				p_cconv(t_pinfo pinfo, t_pab *s_buf, va_list ap);
int				pbuff_char(t_pab *s_buf, size_t len, char c);
/*
**	In file p_padd.c
*/

int				p_padd(t_pab *s_buf, size_t len, t_pinfo pinfo);

/*
**	In file p_prec.c
*/

int				p_prec(t_pab *s_buf, size_t len, t_pinfo pinfo);

/*
**	In file numeric_conv.c
*/

int				numeric_conv(t_pab *s_buf, long long arg, \
		int base, t_pinfo pinfo);
#endif
