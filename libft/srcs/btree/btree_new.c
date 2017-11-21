#include "btree.h"
#include "libft.h"

t_btree	*btree_new(void *data)
{
	t_btree	*new;

	if (!(new = ft_memalloc(sizeof(t_btree))))
		return (NULL);
	new->data = data;
	return (new);
}
