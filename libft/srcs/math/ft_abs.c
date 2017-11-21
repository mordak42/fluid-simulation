#include <stdint.h>
#include "libft.h"
#include <sys/types.h>

intmax_t	ft_abs(intmax_t value)
{
	return ((value >= 0) ? (long)value : (long)-(value));
}
