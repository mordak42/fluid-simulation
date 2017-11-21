#include "libft.h"
#include "str.h"
#include "alloc.h"

char	*ft_chartostr(char c)
{
	char	*str;

	str = palloc(2);
	str[0] = c;
	str[1] = 0;
	return (str);
}
