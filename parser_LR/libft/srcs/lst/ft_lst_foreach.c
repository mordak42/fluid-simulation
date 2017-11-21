#include "libft.h"
#include "list.h"

void	ft_double_lst_foreach(t_list_d *start, t_list_d *end, \
		void (*f)(t_list_d*), int order)
{
	if (start)
	{
		if (order == 1)
		{
			while (start != end)
			{
				(*f)(start);
				start = start->next;
			}
		}
		else if (order == -1)
		{
			while (start != end)
			{
				(*f)(start);
				start = start->prev;
			}
		}
	}
}

void	ft_simple_lst_foreach(t_list *start, t_list *end, void (*f)(t_list*))
{
	if (start)
	{
		while (start != end)
		{
			(*f)(start);
			start = start->next;
		}
	}
}
