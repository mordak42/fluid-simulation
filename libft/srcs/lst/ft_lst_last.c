#include "libft.h"

t_list	*ft_last_simple_lst(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	*ft_genlst_last(void *lst)
{
	t_gen_lst	*lst_cast;

	lst_cast = lst;
	while (lst_cast && lst_cast->next)
		lst_cast = lst_cast->next;
	return (lst_cast);
}

t_list	*ft_previous_last_simple_lst(t_list *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst && lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}
