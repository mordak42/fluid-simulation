#include "libft.h"

int		ft_sqrt(int nb)
{
	int	div;

	div = 0;
	if (nb < 0)
		nb *= -1;
	while (div++ != nb)
	{
		if ((nb / div) < div)
			break ;
		if (nb / div == div)
			return ((nb % div == 0) ? div : 0);
	}
	return (0);
}
