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
		while(1)
		{
			sleep(1);
			//这里是子进程
			printf("This is child! pid = %d ppid = %d\n", getpid(),getppid());
		}
	}
	//这里是父进程

	printf("fork test!\n");

	system("clear");
	return 0;
}
