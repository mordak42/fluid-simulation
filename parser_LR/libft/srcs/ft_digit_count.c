#include "libft.h"

int		ft_digit_count(int nb)
{
	int		nb_digit;

	nb_digit = 1;
	while (nb > 10)
	{
		nb_digit++;
		nb /= 10;
	}
	return (nb_digit);
}
