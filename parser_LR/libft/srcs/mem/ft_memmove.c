#include "libft.h"
#include "mem.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst >= src && dst <= src + len)
	{
		while (len--)
			*(unsigned char*)(dst + len) = *(unsigned char*)(src + len);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
