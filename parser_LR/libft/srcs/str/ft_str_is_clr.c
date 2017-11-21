#include "str.h"
#include "libft.h"

int		ft_str_is_clr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		ft_str_is_clear_n(char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && n)
	{
		if (!ft_is_space(str[i]))
			return (FALSE);
		--n;
		++i;
	}
	return (TRUE);
}
