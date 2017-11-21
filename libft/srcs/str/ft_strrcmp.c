#include "libft.h"
#include "str.h"
#include <stdio.h>

/*
**	Can we find the string little at the end of big ?
*/

int	ft_strrcmp(const char *big, const char *little)
{
	int		big_index;
	int		little_index;

	big_index = ft_strlen(big) - 1;
	little_index = ft_strlen(little) - 1;
	if (little_index > big_index)
		return (-1);
	while (big_index && little_index && big[big_index] == little[little_index])
	{
		big_index--;
		little_index--;
	}
	if (little_index == 0 && big[big_index] == little[little_index])
		return (0);
	return (big[big_index] - little[little_index]);
}
