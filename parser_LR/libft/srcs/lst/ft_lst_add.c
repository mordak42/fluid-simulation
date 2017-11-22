#include "libft.h"
#include "list.h"

void	ft_simple_lst_add(t_list **first, t_list *new_node)
{
	if (new_node)
	{
		if (*first != NULL)
			new_node->next = *first;
		*first = new_node;
	}
}

void	ft_genlst_add(void **first, void *new)
{
	t_gen_lst **first_cast = (t_gen_lst **)first;
	t_gen_lst *new_cast = new;

	if (new)
	{
		if (*first_cast != NULL)
			new_cast->next = *first_cast;
		*first_cast = new_cast;
	}
}

void	ft_double_lst_add(t_lst_head **head, t_list_d *new_node)
{
	if (new_node)
	{
		if ((*head)->first)
		{
			new_node->next = (*head)->first;
			(*head)->first->prev = new_node;
			(*head)->first = new_node;
			(*head)->shift_middle -= 1;
			(*head)->node_count += 1;
		}
		else
		{
			(*head)->node_count += 1;
			(*head)->first = new_node;
			(*head)->middle = new_node;
		}
	}
	ft_lst_replace_middle(head);
}
