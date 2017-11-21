#ifndef SYSTEM_H
# define SYSTEM_H
#include "libft.h"
#include <errno.h>
#include <stdio.h>

size_t	get_ws_col(void);
size_t	get_ws_row(void);
void	put_termcap(char *capacity);
void	put_ntermcap(char *capacity, int n);
void	goto_termcap(char *capacity, int co, int li);
void	p_pipe(int	mypipe[2]);
int		p_fork(void);
char	*ft_gethome(void);

#endif
