#include "libft.h"
#include "str.h"

ssize_t		ft_strichr(const char *s, int c)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}
