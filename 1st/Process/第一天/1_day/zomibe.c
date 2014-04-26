#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int a = 100;

int main(void)
{
	pid_t pid;
	int i = 10;

	while(i--)
	{
		pid = fork();
		if(pid == 0)
		{
			printf("This is clild\n");
			exit(0);
		}
	}
	//这里是父进程
///	while(1)
//	   ;

	printf("fork test!\n");

	system("clear");
	return 0;
}
