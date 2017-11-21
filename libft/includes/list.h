#ifndef LIST_H
# define LIST_H

#include <stdlib.h>

typedef struct		s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

typedef struct		s_list_d
{
	struct s_list_d	*next;
	struct s_list_d	*prev;
	void			*data;
}					t_list_d;

typedef struct		s_lst_head
{
	struct s_list_d	*first;
	struct s_list_d	*middle;
	struct s_list_d	*last;
	int				shift_middle;
	int				node_count;
}					t_lst_head;

typedef struct	s_listint
{
	int					data;
	struct s_listint	*next;
}				t_listint;

typedef struct	s_gen_lst
{
	struct s_gen_lst	*next;
}				t_gen_lst;

t_list		*ft_lst_pop(t_list **list);

/*
**	In file listint.c
*/

int					ft_lstint_pop(t_listint **list);
t_listint			*ft_lstint_new(int data);
void				ft_lstint_add(t_listint **stack, int state);

/*
**	In file ft_lst_add.c
*/

void				ft_genlst_add(void *first, void *new);
void				ft_simple_lst_add(t_list **first, t_list *new_node);
void				ft_double_lst_add(t_lst_head **head, t_list_d *new_node);

/*
**	In file ft_lst_create.c
*/

t_list				*ft_simple_lst_create(void *data);
t_list_d			*ft_double_lst_create(void *data);
t_lst_head			*ft_create_head(t_list_d *first);

/*
**	In file ft_lst_del_one.c
*/

void				ft_double_lst_del_one(t_lst_head **head, \
		t_list_d *node, void (*f)(void*));

/*
**	in file simple_lst_del_one.c
*/

void				ft_simple_lst_del_one(t_list **first, \
		t_list *node, void(*f)(void*));
void	ft_genlst_del_one(void *first, void *node, void (*f)(void*));

/*
**	In file ft_lst_dup.c
*/

void				ft_simple_lst_dup(t_list **new_list_first, \
		t_list *original);

/*
**	In file ft_lst_for_n.c
*/

void				ft_double_lst_for_n(t_list_d *start, int count, \
		void (*f)(t_list_d*), int order);
void				ft_simple_lst_for_n(t_list *start, \
		int count, void (*f)(t_list*));

/*
**	In file ft_lst_foreach.c
*/

void				ft_double_lst_foreach(t_list_d *start, t_list_d *end, \
		void (*f)(t_list_d*), int order);
void				ft_simple_lst_foreach(t_list *start, \
		t_list *end, void (*f)(t_list*));

/*
**	In file ft_lst_get_n.c
*/

t_list_d			*ft_double_lst_get_n(t_list_d *first, int n);
t_list				*ft_simple_lst_get_n(t_list	*first, size_t n);

/*
**	In file ft_lst_last.c
*/

t_list				*ft_last_simple_lst(t_list *lst);
void				*ft_genlst_last(void *lst);
t_list				*ft_previous_last_simple_lst(t_list *lst);

/*
**	In file ft_lst_pushback.c
*/

void	ft_genlst_pushback(void *first, void *new_node);
void				ft_simple_lst_pushback(t_list **first, t_list *new_node);
void				ft_double_lst_pushback(t_lst_head **head, \
		t_list_d *new_node);

/*
**	In file ft_lst_remove.c
*/

void				ft_simple_lst_remove(t_list	**first, void (*f)(void*));
void				ft_double_lst_remove(t_lst_head **head, void (*f)(void*));
void				ft_remove_head(t_lst_head **head, void (*f)(void*));
void				ft_genlst_remove(void *first, void (*f)(void*));

/*
**	In file ft_lst_return_if.c
*/

t_list_d			*ft_double_lst_return_if(t_list_d *starting_point, \
		int (*f)(void*), int order);
t_list				*ft_simple_lst_return_if(t_list *starting_point, \
		int (*f)(void*));

/*
**	In file ft_lst_sort_insert.c
*/

void				ft_simple_lst_sort_insert(t_list **first, \
		t_list *new_node, int (*f)(t_list*, t_list*));
void				ft_lst_replace_middle(t_lst_head **head);
void				ft_double_lst_sort_insert(t_lst_head **head, \
		t_list_d *new_node, int (*f)(t_list_d*, t_list_d*));

/*
**	in file ft_lst_iteri.c
*/

void				ft_double_lst_iteri(t_list_d *start, \
		t_list_d *end, void (*f)(t_list_d*, size_t), int order);
void				ft_simple_lst_iteri(t_list *start, \
		t_list *end, void (*f)(t_list*, size_t));

size_t				ft_lst_len(t_list *lst);

/*
**	in file ft_lst_iteri.c
*/

void				ft_simple_lst_rev(t_list **lst);

#endif
