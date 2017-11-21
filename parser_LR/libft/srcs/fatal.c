#include "libft.h"
#include "str.h"

void	fatal(const char *error_str)
{
	if (error_str != NULL)
		ft_putendl(error_str);
	exit(1);
}
