#include "str.h"
#include "mem.h"
#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s)
		s++;
	if (*s == c)
		return ((char*)s);
	return (NULL);
}
