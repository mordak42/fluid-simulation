#include "libft.h"
#include <pwd.h>

char	*ft_gethome(void)
{
	uid_t	uid;
	struct passwd *pw;

	uid = getuid();
	pw = getpwuid(uid);
	if (!pw)
		return (NULL);
	return (pw->pw_dir);
}
