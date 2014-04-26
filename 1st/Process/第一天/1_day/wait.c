#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int a = 100;

int main(void)
{
	pid_t pid;
	int status;

	pid = fork();
	if(pid == 0)
	{
		sleep(1);
		//这里是子进程
//		char *p;
//	       	*p = 'a';
		int a = 10/0;

		printf("This is child!\n");
		exit(100);
	}
	if(pid > 0)
	{
		wait(&status);
		if(WIFEXITED(status))
		{
			//子进程正常结束
			printf("Normal_exit status =  %d\n", WEXITSTATUS(status));
		}
		if(WIFSIGNALED(status))
		{
			//子进程非正常结束
			printf("unNormal_exit status =  %d\n", WTERMSIG(status));

		}
		//这里是父进程
		printf("This is parent!a = %d\n", a);
	}


	printf("fork test!\n");

	return 0;
}
