#include "libft.h"

void	ft_sort_int_tab(int *tab, size_t n)
{
	int		tmp;
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < n)
	{
		j = i;
		while (++j < n)
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
	}
}
