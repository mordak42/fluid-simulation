#include "system.h"

void	p_pipe(int	mypipe[2])
{
	if (pipe (mypipe) < 0)
	{
		perror ("pipe");
		exit (1);
	}
}
