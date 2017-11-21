#include "libft.h"
#include "str.h"
#include "alloc.h"
#include "mem.h"

char	*ft_strdup(const char *s1)
{
	char	*new_str;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	new_str = palloc(sizeof(*new_str) * len);
	ft_memcpy(new_str, s1, len);
	return (new_str);
}

char	*cl_strdup(const char *s1)
{
	char	*new_str;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	new_str = ft_memalloc(sizeof(*new_str) * len);
	ft_memcpy(new_str, s1, len);
	return (new_str);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new_str;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	new_str = palloc(sizeof(*new_str) * n + 1);
	ft_memcpy(new_str, s1, n);
	new_str[n] = 0;
	if (n > s1_len)
		ft_bzero(new_str + s1_len, n - s1_len);
	return (new_str);
}

char	*cl_strndup(const char *s1, size_t n)
{
	char	*new_str;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	new_str = ft_memalloc(sizeof(*new_str) * n + 1);
	ft_memcpy(new_str, s1, n);
	new_str[n] = 0;
	if (n > s1_len)
		ft_bzero(new_str + s1_len, n - s1_len);
	return (new_str);
}
