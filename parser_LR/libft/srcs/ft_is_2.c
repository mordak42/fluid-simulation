#include "libft.h"

int		ft_is_lower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int		ft_is_one_of(char c, const char *that)
{
	int	i;

	i = 0;
	while (that[i])
	{
		if (c == that[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int		ft_is_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int		ft_is_hex(int c)
{
	if ((c >= 'A' && c <= 'F') || ft_isdigit(c) || (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}
