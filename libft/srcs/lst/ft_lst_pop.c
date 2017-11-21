#include "list.h"

t_list	*ft_lst_pop(t_list **list)
{
	t_list	*res;

	res = *list;
	if (*list)
		*list = (*list)->next;
	return (res);
}
