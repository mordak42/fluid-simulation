#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include "color.h"
# include "str.h"
# include "mem.h"
# include "alloc.h"
# include "list.h"
# include "array.h"
# include "system.h"
# include "btree.h"
# include "string.h"
# define MALLOC_ERROR 666
# define TRUE 1
# define FALSE 0
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define WHITESPACES " 	\n\t\v"
# define IS_WHITESPACE(c) (c == 32 || c == 9 || c == 10)
# ifndef T_ULONG
#  define T_ULONG

typedef unsigned long int	t_ulong;
# endif

typedef struct		s_coor
{
	int		x;
	int		y;
}					t_coor;

/*
** In file ft_abs.c
*/

intmax_t			ft_abs(intmax_t value);

/*
** In file ft_atoi.c
*/

int					ft_atoi(const char *str);
int					ft_atoi_safe(const char *str, int *result);
intmax_t			ft_atoi_base(char *str, int base);

/*
**	In file ft_is_1.c
*/

int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);

/*
**	In file ft_is_2.c
*/

int					ft_is_hex(int c);
int					ft_is_upper(char c);
int					ft_is_lower(char c);
int					ft_is_space(char c);
int					ft_is_one_of(char c, const char *that);

/*
**	In file ft_is_3.c
*/

int					is_quote(int c);

/*
** 	In file toupper.c
*/

int					ft_toupper(int c);
char				*ft_upstr(char *s);

/*
**	In file tolower.c
*/

int					ft_tolower(int c);
char				*ft_lowstr(char *s);

/*
**	In file itoa.c
*/

char				*ft_itoa(int n);
char				*ft_itoa_base(intmax_t value, int base);
char				*ft_unsigned_itoa_base(uintmax_t value, int base);
int					uitoa_base_len(uintmax_t value, int base);
int					itoa_base_len(intmax_t value, int base);

/*
**	Fatal.c
*/

/*
**	in fule putnbr.c
*/

void				ft_putnbr(int n);

void				fatal(const char *error_str);
int					ft_is_executable(char *dir, char *file);

void				ft_strpush(char **str, char c);
int					ft_strarrstrn(char **array, char *str, unsigned int n);
unsigned int		ft_parrlen(void **array);
void				ft_parrpush(void ***tablo, void *elem);
void				**ft_parrnew(void);
void	ft_strspush(char **str, char *push);

#endif
