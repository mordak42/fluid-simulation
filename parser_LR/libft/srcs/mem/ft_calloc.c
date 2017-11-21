#include "alloc.h"
#include "mem.h"
#include "str.h"
#include "color.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count * size == 0)
	{
		ft_putendl("Calloc exit");
		exit(1);
	}
	mem = malloc(count * size);
	if (!mem)
	{
		ft_putendl("Calloc exit");
		exit(1);
	}
	ft_bzero(mem, size);
	return (mem);
}
