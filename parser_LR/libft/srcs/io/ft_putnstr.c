#include "libft.h"

void	ft_putnstr(char *str, size_t len)
{
	unsigned int strlen;

	strlen = ft_strlen(str);
	if (strlen > len)
		write(1, str, len);
	else
		write(1, str, strlen);
}

void	ft_putnstr_fd(int fd, char *str, size_t len)
{
	unsigned int strlen;

	strlen = ft_strlen(str);
	if (strlen > len)
		write(fd, str, len);
	else
		write(fd, str, strlen);
}
