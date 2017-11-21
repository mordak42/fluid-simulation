#include "libft.h"
#include "str.h"

void				*ft_strchange(void *old, void *new)
{
	free(old);
	return (new);
}

unsigned long int	ft_freeswap(unsigned long int old, unsigned long int new)
{
	free((void*)old);
	return (new);
}
