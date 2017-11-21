#include "array.h"
#include "libft.h"

char			**ft_arrayjoin(char const **s1, char const **s2)
{
	char	**new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_arraylen(s1);
	s2_len = ft_arraylen(s2);
	new_str = palloc(sizeof(char *) * (s1_len + s2_len + 1));
	new_str[s1_len + s2_len] = 0;
	ft_memcpy(new_str, s1, s1_len * sizeof(char *));
	ft_memcpy(&new_str[s1_len], s2, s2_len * sizeof(char *));
	return (new_str);
}

static void		delete_array(char **s1, char **s2, int delete)
{
	if (delete & 2)
		free(s1);
	if (delete & 1)
		free(s2);
}

char			**ft_arrayjoin_free(char **s1, char **s2, int delete)
{
	char	**res;

	res = ft_arrayjoin((const char **)s1, (const char **)s2);
	delete_array(s1, s2, delete);
	return (res);
}
