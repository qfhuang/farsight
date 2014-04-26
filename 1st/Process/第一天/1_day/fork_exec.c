#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int a = 100;

int main(void)
{
	pid_t pid;

	pid = fork();
	if(pid == 0)
	{
		printf("This is child!888888888888888888888");
		execlp("ls", "ls", "-al", NULL);
		//这里是子进程
		exit(0);
	}
	if(pid > 0)
	{
		sleep(1);
		//这里是父进程
		printf("This is parent!a = %d\n", a);
	}


	printf("fork test!\n");

	return 0;
}
