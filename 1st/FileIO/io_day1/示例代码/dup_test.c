#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(void)
{
	int fd = -1;

	if((fd = open("hehe", O_WRONLY|O_CREAT, 0664)) < 0)
	{
		perror("open fd failed!");
	}

	//int fd = dup(1);
	dup2(fd, STDOUT_FILENO);
	printf("haha!");
	printf("%d\n", BUFSIZ);

	return 0;
}
