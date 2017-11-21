#ifndef STR_H
# define STR_H
# include <string.h>
# include <stdlib.h>
# ifdef __x86_64__
#  define LOMAGIC (((0x01010101UL << 16) << 16) | 0x01010101UL)
#  define HIMAGIC (((0x80808080UL << 16) << 16) | 0x80808080UL)
#  define MAGIC_BIT (((0x7efefefeL << 16) << 16) | 0xfefefeffL)
#  ifndef ULONG_SIZE
#   define ULONG_SIZE 8
#  endif
# else
#  define LOMAGIC 0x01010101UL
#  define HIMAGIC 0x80808080UL
#  define MAGIC_BIT 0x7efefefeUL
#  ifndef ULONG_SIZE #   define ULONG_SIZE 4
#  endif
# endif
# ifndef HAS_ZERO
#  define HAS_ZERO(x) ((x - LOMAGIC) & ((~x & HIMAGIC)))
# endif
# ifndef HAS_VALUE
#  define HAS_VALUE(x, n) (HAS_ZERO((x ^ n)))
# endif
# ifndef WHITESPACES
#  define WHITESPACES " 	\n\t\v"
# endif

/*
** In file ft_strlen.c
*/

size_t				ft_strlen(const char *s);
size_t				ft_strlen_color(char *s);

/*
** In file ft_putstr.c
*/
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);

void				ft_putnstr(char *str, size_t len);
void				ft_putnstr_fd(int fd, char *str, size_t len);
/*
** In file ft_putchar.c
*/

int					ft_putchar(int c);
void				ft_putchar_fd(int c, int fd);

/*
**	In file ft_strchr.c
*/

char				*ft_strchr(const char *s, int c);

/*
**	In file ft_strichr.c
*/

ssize_t				ft_strichr(const char *s, int c);

/*
**	In file ft_strrchr.c
*/

char				*ft_strrchr(const char *s, int c);
ssize_t				ft_strrichr(const char *s, int c);

/*
**	In file ft_strcpy.c
*/

char				*ft_strcpy(char *dst, const char *src);

/*
**	In file ft_strncpy.c
*/

char				*ft_strncpy(char *dst, const char *src, size_t len);

/*
**	In file ft_strcmp.c
*/

int					ft_strcmp(const char *s1, const char *s2);

/*
**	In file ft_strncmp.c
*/

int					ft_strncmp(const char *s1, const char *s2, size_t n);

/*
**	In file ft_strdup.c
*/

char				*ft_strdup(const char *s1);
char				*cl_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
char				*cl_strndup(const char *s1, size_t n);

/*
**	In ft_strstr.c
*/

char				*ft_strstr(const char *big, const char *little);

/*
**	In ft_strnstr.c
*/

char				*ft_strnstr(const char *big, \
		const char *little, size_t len);

/*
**	In ft_strrstr.c
*/

char				*ft_strrstr(const char *big, const char *little);

/*
**	In file ft_strcat.c
*/

char				*ft_strcat(char *s1, const char *s2);

/*
**	In file ft_strjoin3_free.c
*/
char				*ft_strjoin3_free(char *s1, char *s2, char *s3, int del);

/*
**	In file ft_strncat.c
*/

char				*ft_strncat(char *s1, const char *s2, size_t n);

/*
**	In file ft_strlcat.c
*/

size_t				ft_strlcat(char *dst, const char *src, size_t size);

/*
** 	In file ft_strnew.c
*/

char				*ft_strnew(size_t size);

/*
** ft_strdel.c
*/

void				ft_strdel(char **as);

/*
**	ft_strclr.c
*/

void				ft_strclr(char *s);

/*
**	striter.c
*/

void				ft_striter(char *s, void (*f)(char *));

/*
**	striter.c
*/

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
**	strmap.c
*/

char				*ft_strmap(char const *s, char (*f)(char));

/*
**	strmapi.c
*/

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
**	ft_strequ.c
*/

int					ft_strequ(char const *s1, char const *s2);

/*
**	ft_strnequ.c
*/

int					ft_strnequ(char const *s1, char const *s2, size_t n);

/*
**	ft_strsub.c
*/

char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*cl_strsub(char const *s, unsigned int start, size_t len);

/*
**	Ft_strjoin.c
*/

char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, char *s2, int delete);
char				*cl_strjoin(char const *s1, char const *s2);

/*
**	strtrim.c
*/

char				*ft_strtrim_sequence(const char *s, const char *sequence);
char				*ft_strtrim(char const *s);

char				**ft_strsplit(char const *s, const char *str);

char				**ft_strsplit_keep(const char *str, const char *split_base);

char				**ft_strsplit_quotes(const char *str, \
		const char *split_base);

void				*ft_strchange(void *old, void *new);

/*
**	Charcmp.c
*/

short int			charcmp(const char *str, size_t i, char c);

/*
**	buff_wchar.c
*/

char				*ft_buff_wchar(wchar_t c);
char				*ft_buff_wstring(wchar_t *str);

/*
**	ft_chartostr.c
*/

char				*ft_chartostr(char c);

/*
**	ft_strmatch.c
*/

int					ft_strmatch(char *s1, char *s2);

/*
**	ft_strnreplace.c
*/

void				ft_strnreplace(char *str, char target, \
		char replace, int size);

/*
** 	In file ft_Strsurround.c
*/

char				*ft_strsurround(const char *s1, \
		const char *s2, const char *s3);

/*
**	In file ft_strrcmp.c
*/

int					ft_strrcmp(const char *s1, const char *s2);

/*
**	In file ft_strrequ.c
*/

int					ft_strrequ(const char *s1, const char *s2);

int					ft_str_is_clr(char *str);
int					ft_str_isdigit(const char *s);

int					ft_is_backslash(char *str, int n);

char				*ft_itoa_word(int n, char nbr[20]);
int					ft_str_is_clear_n(char *str, size_t n);
int			ft_atoilong_safe(const char *str, char **end_ptr, long *result);
#endif
