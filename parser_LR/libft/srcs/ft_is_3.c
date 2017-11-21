#include "libft.h"

int		is_quote(int c)
{
	if (c == '"' || c == '\'' || c == 92)
		return (1);
	return (0);
}
