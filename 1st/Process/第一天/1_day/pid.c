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
		//这里是子进程
		printf("This is child! pid = %d ppid = %d\n", getpid(),getppid());
		exit(0);
	}
	if(pid > 0)
	{
		sleep(1);
		//这里是父进程
		printf("fork_pid = %d\n", pid);
		printf("This is parent!a = %d  pid = %d ppid = %d\n", a, getpid(), getppid());
	}


	printf("fork test!\n");

	return 0;
}
