#include "libft.h"
#include "list.h"

t_list_d	*ft_double_lst_return_if(t_list_d *starting_point, \
		int (*f)(void*), int order)
{
	while (starting_point)
	{
		if ((f)(starting_point->data) == 1)
			return (starting_point);
		if (order == 1)
			starting_point = starting_point->next;
		else if (order == 2)
			starting_point = starting_point->prev;
	}
	return (NULL);
}

t_list		*ft_simple_lst_return_if(t_list *starting_point, int (*f)(void*))
{
	while (starting_point)
	{
		if ((f)(starting_point->data) == 1)
			return (starting_point);
		starting_point = starting_point->next;
	}
	return (NULL);
}
