#include "libft.h"

int		ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	else
		return (nb * ft_power(nb, power - 1));
}
