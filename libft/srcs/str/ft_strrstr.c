#include "libft.h"
#include "str.h"

/*
**	Looks for the very last occurence of the nul terminated string little in
**	the nul terminated string big.
*/

char				*ft_strrstr(const char *big, const char *little)
{
	const char	*found;
	const char	*tmp;
	size_t		len;

	len = ft_strlen(big);
	found = NULL;
	while ((tmp = ft_strnstr(big, little, len)))
	{
		found = tmp;
		big = tmp + 1;
	}
	return ((char*)found);
}
