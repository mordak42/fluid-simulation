#include "libft.h"
#include "list.h"

void	ft_simple_lst_pushback(t_list **first, t_list *new_node)
{
	t_list	*tmp;
	t_list	*old_tmp;

	if (new_node)
	{
		if (first == NULL || *first == NULL)
			*first = new_node;
		else
		{
			tmp = *first;
			old_tmp = tmp;
			while (tmp)
			{
				old_tmp = tmp;
				tmp = tmp->next;
			}
			old_tmp->next = new_node;
		}
	}
}

void	*ft_genlst_pushback(void **first, void *new_node)
{
	if (!first)
		return NULL;
	if (*first) {
		*first = new_node;
		return new_node;
	}
	t_gen_lst *first_point = *first;
	while (first_point->next)
		first_point = first_point->next;
	first_point->next = new_node;
	return new_node;
}

void	ft_double_lst_pushback(t_lst_head **head, t_list_d *new_node)
{
	t_list_d	*prev;

	if (new_node)
	{
		if ((*head)->last)
		{
			prev = (*head)->last;
			new_node->prev = prev;
			prev->next = new_node;
			(*head)->last = new_node;
			(*head)->shift_middle += 1;
			(*head)->node_count += 1;
		}
		else
		{
			(*head)->node_count += 1;
			(*head)->last = new_node;
			(*head)->middle = new_node;
		}
	}
	ft_lst_replace_middle(head);
}
