#include "libft.h"

size_t	ft_lst_len(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

size_t	ft_genlst_len(void *lst)
{
	t_gen_lst *lst_cast = lst;
	int		i;

	i = 0;
	while (lst_cast)
	{
		lst_cast = lst_cast->next;
		i++;
	}
	return (i);
}

