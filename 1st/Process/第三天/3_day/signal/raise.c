#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>



void sig_catch(int signum)
{
	if(signum == SIGINT)
	{
		printf("get SIGINT....\n");
	}

}

int main(int argc, char *argv[])
{
	signal(SIGINT, sig_catch);
	//signal(SIGINT, SIG_DFL);
	//signal(SIGINT, SIG_IGN);

	raise(SIGINT);
	while(1);


	return 0;

}
