#include "libft.h"

#include <stdlib.h>

void	ft_strspush(char **str, char *push)
{
	char *n_str;
	unsigned int strlen;
	unsigned pushlen;

	strlen = ft_strlen(*str);
	pushlen = ft_strlen(push);
	n_str = (strlen / 32 == (strlen + pushlen) / 32
		&& strlen) ? *str : (char*)ft_memalloc(sizeof(char) * (strlen + pushlen
		+ 32 - (strlen + pushlen) % 32 + 1));
	n_str[strlen + pushlen] = '\0';
	while (pushlen--)
		n_str[strlen + pushlen] = push[pushlen];
	if (n_str == *str)
		return ;
	while (strlen--)
		n_str[strlen] = (*str)[strlen];
	free(*str);
	*str = n_str;
}
