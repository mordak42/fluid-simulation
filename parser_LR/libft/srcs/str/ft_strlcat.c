#include "libft.h"
#include "str.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char*)src);
	if (size > dst_len + 1)
	{
		while (i < (size - dst_len - 1))
		{
			dst[dst_len + i] = src[i];
			i++;
		}
	}
	dst[dst_len + i] = '\0';
	if (size >= dst_len)
		return (dst_len + src_len);
	return (size + src_len);
}
