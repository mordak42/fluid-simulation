#include "libft.h"

int	ft_strarrstrn(char **array, char *str, unsigned int n)
{
	int index;

	index = 0;
	while (array[index] && ft_strncmp(str, array[index], n))
		++index;
	return (array[index]) ? index : -1;
}
