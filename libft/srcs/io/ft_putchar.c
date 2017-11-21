#include "libft.h"
#include "str.h"
#include "mem.h"

int		ft_putchar(int c)
{
	char	s[5];

	ft_bzero(s, 5);
	if (c <= 0x7F)
		s[0] = c;
	else if (c < 0x7FF)
	{
		s[0] = ((c >> 6) + 0xC0);
		s[1] = ((c & 0x3F) + 0x80);
	}
	else if (c < 0xFFFF)
	{
		s[0] = ((c >> 12) + 0xE0);
		s[1] = ((c >> 6 & 0x3f) + 0x80);
		s[2] = ((c & 0x3F) + 0x80);
	}
	else if (c < 0x10FFFF)
	{
		s[0] = ((c >> 18) + 0xF0);
		s[1] = ((c >> 12) + 0x3F);
		s[2] = ((c & 0x3F) + 0x80);
		s[3] = ((c & 0x3F) + 0x80);
	}
	ft_putstr(s);
	return (1);
}

void	ft_putchar_fd(int c, int fd)
{
	char	s[5];

	ft_bzero(s, 5);
	if (c <= 0x7F)
		s[0] = c;
	else if (c < 0x7FF)
	{
		s[0] = ((c >> 6) + 0xC0);
		s[1] = ((c & 0x3F) + 0x80);
	}
	else if (c < 0xFFFF)
	{
		s[0] = ((c >> 12) + 0xE0);
		s[1] = ((c >> 6 & 0x3f) + 0x80);
		s[2] = ((c & 0x3F) + 0x80);
	}
	else if (c < 0x10FFFF)
	{
		s[0] = ((c >> 18) + 0xF0);
		s[1] = ((c >> 12) + 0x3F);
		s[2] = ((c & 0x3F) + 0x80);
		s[3] = ((c & 0x3F) + 0x80);
	}
	ft_putstr_fd(s, fd);
}
