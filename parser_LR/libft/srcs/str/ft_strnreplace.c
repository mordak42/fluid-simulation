#include "libft.h"
#include "str.h"

void	ft_strnreplace(char *str, char target, char replace, int size)
{
	int		i;

	i = 0;
	while (i != size)
	{
		if (str[i] == target)
			str[i] = replace;
		i++;
	}
}
