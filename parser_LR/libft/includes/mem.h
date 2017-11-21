#ifndef MEM_H
# define MEM_H
# include <string.h>
# ifdef __x86_64__
#  ifndef CHAR_TO_SHORT
#   define CHAR_TO_SHORT(c) ((c << 8) | c)
#  endif
#  ifndef CHAR_TO_INT
#   define CHAR_TO_INT(c) ((CHAR_TO_SHORT(c) << 16) | CHAR_TO_SHORT(c))
#  endif
#  ifndef CHAR_TO_LONG
#   define CL(c) ((((long)CHAR_TO_INT(c) << 16) << 16) | (long)CHAR_TO_INT(c))
#   define CHAR_TO_LONG(c) CL(c)
#  endif
#  ifndef ULONG_SIZE
#   define ULONG_SIZE 8
#  endif
# else
#  ifndef ULONG_SIZE
#   define ULONG_SIZE 4
#  endif
# endif

/*
**	In file ft_bzero.c
*/

void	ft_bzero(void *s, size_t n);

/*
**	In file ft_memset.c
*/

void	*ft_memset(void *b, int c, size_t len);

/*
**	In file ft_memcpy.c
*/

void	*ft_memcpy(void *dst, const void *src, size_t n);

/*
**	In file ft_memchr.c
*/

void	*ft_memchr(const void *s, int c, size_t n);

/*
**	in file ft_memmove.c
*/

void	*ft_memmove(void *dst, const void *src, size_t len);

/*
**	In file memccpy.c
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n);

/*
**	memcmp.c
*/

int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*
**	ft_memdel.c
*/
void	ft_memdel(void **ap);

/*
**	ft_free.c
*/
void	ft_free(void *p);
#endif
