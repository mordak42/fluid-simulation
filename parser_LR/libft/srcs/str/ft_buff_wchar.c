#include "libft.h"
#include "mem.h"
#include "str.h"

char	*ft_buff_wchar(wchar_t c)
{
	char	*s;

	s = malloc(sizeof(char) * 4 + 1);
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
	return (s);
}

char	*ft_buff_wstring(wchar_t *str)
{
	char	*new_str;
	char	*old_str;
	char	*tmp_wchar;

	new_str = malloc(1);
	if (!new_str)
		exit(1);
	new_str[0] = 0;
	while (*str != 0)
	{
		tmp_wchar = ft_buff_wchar(*str);
		old_str = new_str;
		new_str = ft_strjoin(new_str, tmp_wchar);
		str++;
		free(old_str);
		free(tmp_wchar);
	}
	return (new_str);
}
