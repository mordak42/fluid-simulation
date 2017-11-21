#include "libft.h"

unsigned int	ft_parrlen(void **array)
{
	void	**beg;

	beg = array;
	while (*array)
		++array;
	return ((unsigned int)(array - beg));
}
