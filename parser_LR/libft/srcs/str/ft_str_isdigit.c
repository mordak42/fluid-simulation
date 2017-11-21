#include "libft.h"

int		ft_str_isdigit(const char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (FALSE);
		++s;
	}
	return (TRUE);
}
