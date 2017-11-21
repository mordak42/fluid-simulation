#include "libft.h"
#include "str.h"

int			ft_atoi(const char *str)
{
	int		neg;
	int		res;

	neg = 0;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (neg ? -(res) : res);
}

static int	set_result_int(int *result)
{
	*result = -2147483648;
	return (1);
}

int			ft_atoi_safe(const char *str, int *result)
{
	int	sign;

	*result = 0;
	sign = 0;
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (ft_strcmp(str, "-2147483648") == 0)
		return (set_result_int(result));
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '-' ? -1 : 1);
		str++;
	}
	if (*str == '\0')
		return (0);
	while ('0' <= *str && *str <= '9')
	{
		*result = (*result * 10) + (*str - '0');
		str++;
	}
	*result = sign == -1 ? -(*result) : *result;
	if (*str != '\0')
		return (0);
	return (1);
}

static long	set_result_long(long *result)
{
	*result = 0x1000000000000000;
	return (1);
}

int			ft_atoilong_safe(const char *str, char **end_ptr, long *result)
{
	int	sign;

	*result = 0;
	sign = 0;
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (ft_strcmp(str, "-9223372036854775808") == 0)
		return (set_result_long(result));
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '-' ? -1 : 1);
		str++;
	}
	if (*str == '\0')
		return (0);
	while ('0' <= *str && *str <= '9')
	{
		*result = (*result * 10) + (*str - '0');
		str++;
	}
	*result = sign == -1 ? -(*result) : *result;
	*end_ptr = (char *)str;
	return (1);
}

intmax_t	ft_atoi_base(char *str, int base)
{
	int			i;
	intmax_t	res;
	int			neg;

	neg = 0;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = 1;
		i++;
	}
	while (ft_is_hex(str[i]))
	{
		if (str[i] - 'A' >= 0)
			res = res * base + (str[i] - 55);
		else
			res = res * base + (str[i] - 48);
		i++;
	}
	return ((neg == 1) ? -(res) : res);
}
