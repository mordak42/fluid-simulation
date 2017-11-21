#include "libft.h"
#include "mem.h"
#include "str.h"

char	*ft_strsurround(const char *s1, const char *s2, const char *s3)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	new_str = palloc(sizeof(*new_str) * (s1_len + s2_len + s3_len + 1));
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	ft_memcpy(new_str + s1_len + s2_len, s3, s3_len);
	new_str[s1_len + s2_len + s3_len] = 0;
	return (new_str);
}
