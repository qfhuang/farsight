#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int fd = -1;

	if(0==access("haha", R_OK|W_OK))
		printf(" can read ,can write!\n");
	else
		printf(" can not read ,can not write!\n");

	if((fd = open("haha", O_WRONLY|O_CREAT, 0664)) == -1)
	{
		fprintf(stderr, "failed!%s\n", strerror(errno));
	}

	write(fd, "haha!", 7);

	close(fd);


	return 0;
}
