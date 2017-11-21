#include "libft.h"
#include "list.h"

void	ft_double_lst_for_n(t_list_d *start, int count, void (*f)(t_list_d*), \
		int order)
{
	while (start && count)
	{
		(*f)(start);
		if (order == 1)
			start = start->next;
		if (order == -1)
			start = start->prev;
		count--;
	}
}

void	ft_simple_lst_for_n(t_list *start, int count, void (*f)(t_list*))
{
	while (start && count)
	{
		(*f)(start);
		start = start->next;
		count--;
	}
}
