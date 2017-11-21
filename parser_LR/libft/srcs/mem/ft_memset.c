#include "libft.h"
#include "mem.h"

/*
**	Align memory
*/

static void	align_memory(unsigned char **ptr, int c, size_t *n)
{
	while (*n && (((t_ulong)*ptr & (ULONG_SIZE - 1)) != 0))
	{
		(*n)--;
		**ptr = (unsigned char)c;
		(*ptr)++;
	}
}

/*
**	Set len bytes from ptr to 0
*/

static void	cpy_longword(size_t len, t_ulong **ul_ptr, int c)
{
	size_t	xlen;

	xlen = (len / ULONG_SIZE) + 1;
	while (--xlen)
	{
		**ul_ptr = (t_ulong)(CHAR_TO_LONG((unsigned char)c));
		(*ul_ptr)++;
	}
}

void		*ft_memset(void *ptr, int c, size_t len)
{
	t_ulong	*ul_ptr;
	void	*origin;

	origin = ptr;
	align_memory((unsigned char**)&ptr, c, &len);
	ul_ptr = (t_ulong*)ptr;
	if (len >= ULONG_SIZE)
		cpy_longword(len, &ul_ptr, c);
	len %= ULONG_SIZE;
	if (len > 0)
	{
		ptr = ul_ptr;
		while (len)
		{
			len--;
			*(unsigned char*)ptr = (unsigned char)c;
			ptr++;
		}
	}
	return (origin);
}
