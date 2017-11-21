#include "libft.h"

void	**ft_parrnew(void)
{
	void	**arr;

	arr = (void**)ft_memalloc(sizeof(void*));
	*arr = (void*)0;
	return (arr);
}
