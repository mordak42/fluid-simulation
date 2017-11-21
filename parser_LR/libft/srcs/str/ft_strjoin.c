#include "libft.h"
#include "str.h"
#include "alloc.h"
#include "mem.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = palloc(s1_len + s2_len + 1);
	new_str[s1_len + s2_len] = 0;
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	return (new_str);
}

char			*cl_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_memalloc(s1_len + s2_len + 1);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	return (new_str);
}

static void		ft_strdelete(char *s1, char *s2, int delete)
{
	if (delete & 2)
		free(s1);
	if (delete & 1)
		free(s2);
}

char			*ft_strjoin_free(char *s1, char *s2, int delete)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	ft_strdelete(s1, s2, delete);
	return (res);
}
