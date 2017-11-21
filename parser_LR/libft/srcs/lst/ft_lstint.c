#include "list.h"
#include "libft.h"

int		ft_lstint_pop(t_listint **list)
{
	t_listint	*res;

	res = *list;
	if (*list)
		*list = (*list)->next;
	return (res->data);
}

t_listint	*ft_lstint_new(int data)
{
	t_listint	*stack;

	stack = ft_memalloc(sizeof(t_listint));
	stack->data = data;
	return (stack);
}

void	ft_lstint_add(t_listint **stack, int state)
{
	t_listint	*new;
	new = ft_lstint_new(state);
	new->next = *stack;
	*stack = new;
}
