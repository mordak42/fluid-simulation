#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (*s && f)
	{
		(*f)(i, s);
		i++;
		s++;
	}
}
