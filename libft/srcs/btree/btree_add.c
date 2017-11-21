#include "btree.h"
#include "libft.h"
#include <time.h>

t_btree	*btree_join(t_btree **root, t_btree	*new)
{
	new->left = *root;
	*root = new;
	return (*root);
}

t_btree	*btree_join_new(t_btree **root, void *data)
{
	t_btree	*new;

	new = btree_new(data);
	if (!new)
		return (NULL);
	return (btree_join(root, new));
}

#include <stdio.h>
#ifdef RAND_MAX
# undef RAND_MAX
#endif
#define RAND_MAX 3
t_btree	*btree_random(int depth)
{
	t_btree	*new = NULL;
	int		random_path;

	if (depth == 0)
		return (NULL);
//	srand(time(NULL)); // initialisation de rand
	new = btree_new("lala");
	random_path = rand();
	printf("%d\n", random_path);
	if (random_path & 0b1)
		new->left = btree_random(depth - 1);
	if (random_path & 0b10)
		new->right = btree_random(depth - 1);

	return (new);
}
