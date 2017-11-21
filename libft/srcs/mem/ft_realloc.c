#include "libft.h"
#include "alloc.h"
#include "mem.h"

void	*ft_realloc(size_t curr_size, void *ptr, size_t new_size)
{
	void	*new_memory;

	if (!ptr)
		return (palloc(new_size));
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		new_memory = palloc(new_size);
		ft_memcpy(new_memory, ptr, curr_size);
		free(ptr);
	}
	return (new_memory);
}

void	*cl_realloc(size_t curr_size, void *ptr, size_t new_size)
{
	void	*new_memory;

	if (!ptr)
		return (ft_memalloc(new_size));
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		new_memory = ft_memalloc(new_size);
		ft_memcpy(new_memory, ptr, curr_size);
		free(ptr);
	}
	return (new_memory);
}
