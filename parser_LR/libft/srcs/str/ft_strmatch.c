#include "libft.h"
#include <stdio.h>

int			ft_strmatch(char *s1, char *s2)
{
	int			i;
	int			j;
	int			ret;

	i = 0;
	j = 0;
	ret = ft_strlen(s2);
	while (s1[i])
	{
		j = 0;
		while (s1[i] != s2[j] && s1[i] && s2[j])
			j++;
		i++;
		if (j <= ret)
			ret = j;
	}
	if (ret == (int)ft_strlen(s2))
		return (-1);
	return (ret);
}
