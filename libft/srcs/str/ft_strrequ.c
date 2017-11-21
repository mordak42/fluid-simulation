#include "libft.h"
#include "str.h"

int		ft_strrequ(const char *s1, const char *s2)
{
	if (ft_strrcmp(s1, s2) != 0)
		return (0);
	return (1);
}
