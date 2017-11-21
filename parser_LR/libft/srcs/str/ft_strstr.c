#include "libft.h"
#include "str.h"

char	*ft_strstr(const char *big, const char *little)
{
	return (ft_strnstr(big, little, ft_strlen(big)));
}
