#ifndef SELECT_H
# define SELECT_H
# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include "libft.h"
# define CYCLE_OFF 0
# define CYCLE_ON 1
# define UP_ARROW "\E[A"
# define DOWN_ARROW "\E[B"
# define RIGHT_ARROW "\E[C"
# define LEFT_ARROW "\E[D"
# define SL_UP 1
# define SL_DOWN 2
# define SL_LEFT 3
# define SL_RIGHT 4

typedef struct			s_cursor
{
	int			x;
	int			y;
}						t_cursor;

typedef struct			s_select
{
	struct s_cursor		cursor;
	int					li;
	int					co;
	int					argc;
	char				*termtype;
	t_lst_head			*head;
	t_list				*select_lst;
	char				buf[1024];
	char				buf2[4096];
	char				*ap;
	size_t				col_w;
	struct termios		old_term;
	t_list_d			*focused;
}						t_select;

typedef struct			s_sl_node
{
	int					index;
	const char			*content;
	size_t				size;
	t_coordinates		xy;
	int					selected;
	int					focused;
}						t_sl_node;

void					term_out(void);
int						init_term(t_select *sl);
t_select				*get_sl(t_select *sl);
int						get_tty_fd(int call);
t_lst_head				*create_list(char *av[], int argc);
t_sl_node				*create_sl_node(const char *content, int index);
int						get_col_width(t_select *sl);
void					compute_pos(t_list_d *elem);
void					toggle_loop(int cycle);
void					print_all();
void					print_elem(t_list_d *elem);
void					exit_proper(int signum);
void					move_cursor(t_sl_node *node);
void					main_loop();
void					reprint_elem(t_list_d *elem);
void					go_elem(int code);
int						get_diff(t_sl_node	*node, int code);
void					select_elem(void);
void					unselect_elem(t_select *sl);
int						elem_was_selected(void *data);
void					return_selected();
void					free_select_lst_data(void *p);
void					fake_free(void *p);
void					init_sl(t_select *sl, int ac);
void					delete_elem();
void					shift_index(t_list_d *elem);
void					delete_elem(t_list_d *elem);
void					remove_elem(void);
void					sl_resize(int sig);
void					delete_lines(void);
void					no_space(void);
#endif
