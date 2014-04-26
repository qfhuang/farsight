#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>


void sig_handle(int signum)
{
	char buf[128];

	if(signum == SIGCHLD)
	{
	#if 1
		snprintf(buf, 128, "get a child exit");		
		write(1,buf, strlen(buf));
	#else
		printf("get a child exit\n");
	#endif
		wait();
	}
	if(signum == SIGPIPE)
	{
		printf("get a SIGPIPE\n");
	}
	if(signum == SIGALRM)
	{
		printf("get a SIGALRM\n");
		alarm(2);
	}
	
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int ret = -1;
	int pfd[2];
	

	signal(SIGCHLD, sig_handle);
	signal(SIGPIPE, sig_handle);
	signal(SIGALRM, sig_handle);
	
	ret = pipe(pfd);
	if(ret < 0)
	{
		perror("pipe");
		exit(1);
	}	

	pid = fork();
	if(pid == 0)
	{
			
		printf("------in child---------\n");
		close(pfd[0]);

		while(1)
		{
			printf("@_@...........\n");
			sleep(2);
		}


	}
	if(pid > 0)
	{
		alarm(1);
		while(1);

		close(pfd[0]);
		printf("------in parent---------\n");
		sleep(5);
		write(pfd[1], "hello", 5);
		printf("haha i am still here\n");

		sleep(2);
		kill(pid, SIGINT);
		while(1);
		
	}

	return 0;

}
