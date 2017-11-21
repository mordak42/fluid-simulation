#include "str.h"

int		ft_is_backslash(char *str, int n)
{
	int	i;
	int	res;

	res = 0;
	i = n;
	if (i == 0)
		return (0);
	i--;
	while (i >= 0 && str[i] == '\\')
	{
		res = res == 0 ? 1 : 0;
		i--;
	}
	return (res);
}
