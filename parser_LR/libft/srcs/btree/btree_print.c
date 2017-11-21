#include "btree.h"
#include "libft.h"
#include <ncurses.h>

void	aux(t_btree *root, int li, int co, void (printer) (void *))
{
	if (!root)
		return ;
	move(li, co);
	printer(root->data);
	aux(root->left, li + 2, co - 10, printer);
	aux(root->right, li + 2, co + 10, printer);
}

void	btree_print(t_btree *root, void (printer) (void *))
{

	if (!root)
		return ;
	aux(root, 0,  COLS / 2, printer);
}
