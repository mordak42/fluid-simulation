#include "libft.h"
#include "str.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i != len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (ft_strlen(src) < len)
		while (i != len)
		{
			dst[i] = '\0';
			i++;
		}
	return (dst);
}
