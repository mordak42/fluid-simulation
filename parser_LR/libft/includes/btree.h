#ifndef BTREE_H
# define BTREE_H
typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*data;

}				t_btree;

t_btree	*btree_new(void *data);
t_btree	*btree_join(t_btree **root, t_btree	*new);
t_btree	*btree_join_new(t_btree **root, void *data);
t_btree	*btree_random(int depth);
void	btree_print(t_btree *root, void (printer) (void *));
#endif
