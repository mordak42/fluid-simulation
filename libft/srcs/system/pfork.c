#include "system.h"

int		p_fork(void)
{
	pid_t	pid;

	pid = fork();
	//fprintf(stderr, "meuh\n");
	//system("echo b >> log");
	if (pid < 0)
	{
		system("echo a >> toto");
		perror ("fork");
		exit (1);
	}
	return (pid);
}
