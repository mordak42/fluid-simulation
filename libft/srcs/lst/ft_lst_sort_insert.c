#include "libft.h"
#include "list.h"

void		ft_simple_lst_sort_insert(t_list **first, t_list *new_node, \
		int (*f)(t_list*, t_list*))
{
	int		first_ret;
	t_list	*curr_node;
	t_list	*old_node;

	curr_node = *first;
	old_node = curr_node;
	if (new_node)
	{
		if ((f)(*first, new_node) >= 0)
			ft_simple_lst_add(first, new_node);
		else
		{
			first_ret = (*f)(curr_node, new_node);
			while (curr_node && (f)(curr_node, new_node) == first_ret)
			{
				old_node = curr_node;
				curr_node = curr_node->next;
			}
			old_node->next = new_node;
			new_node->next = curr_node;
		}
	}
}

static void	ft_lst_insert_after_middle(t_lst_head **head, t_list_d *new_node, \
		int (*f)(t_list_d*, t_list_d*))
{
	t_list_d	*curr_node;
	t_list_d	*prev_node;
	int			first_ret;

	curr_node = (*head)->middle;
	first_ret = (f)(curr_node, new_node);
	while (curr_node && ((f)(curr_node, new_node) == first_ret))
		curr_node = curr_node->next;
	prev_node = curr_node->prev;
	prev_node->next = new_node;
	new_node->prev = prev_node;
	new_node->next = curr_node;
	curr_node->prev = new_node;
	(*head)->shift_middle += 1;
}

static void	ft_lst_insert_before_middle(t_lst_head **head, t_list_d *new_node, \
		int (*f)(t_list_d*, t_list_d*))
{
	t_list_d	*curr_node;
	t_list_d	*next_node;
	int			first_ret;

	curr_node = (*head)->middle;
	first_ret = (f)(curr_node, new_node);
	while (curr_node && ((f)(curr_node, new_node) == first_ret))
	{
		curr_node = curr_node->prev;
	}
	next_node = curr_node->next;
	next_node->prev = new_node;
	new_node->next = next_node;
	new_node->prev = curr_node;
	curr_node->next = new_node;
	(*head)->shift_middle -= 1;
}

void		ft_lst_replace_middle(t_lst_head **head)
{
	if ((*head)->shift_middle == -2)
	{
		(*head)->middle = (*head)->middle->prev;
		(*head)->shift_middle = 0;
	}
	if ((*head)->shift_middle == 2)
	{
		(*head)->middle = (*head)->middle->next;
		(*head)->shift_middle = 0;
	}
}

void		ft_double_lst_sort_insert(t_lst_head **head, t_list_d *new_node, \
		int (*f)(t_list_d*, t_list_d*))
{
	int		first_cmp;
	int		middle_cmp;
	int		last_cmp;

	first_cmp = (f)((*head)->first, new_node);
	middle_cmp = (f)((*head)->middle, new_node);
	last_cmp = (f)((*head)->last, new_node);
	(first_cmp >= 0) ? ft_double_lst_add(head, new_node) : 0;
	(last_cmp <= 0 && first_cmp < 0) ? \
	ft_double_lst_pushback(head, new_node) : 0;
	(middle_cmp <= 0 && last_cmp > 0) ? \
	ft_lst_insert_after_middle(head, new_node, f) : 0;
	(middle_cmp >= 0 && first_cmp < 0) ? \
	ft_lst_insert_before_middle(head, new_node, f) : 0;
	(*head)->node_count += 1;
	ft_lst_replace_middle(head);
}
