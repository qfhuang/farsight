#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int fd = -1;
	fd = open("test.c", O_WRONLY|O_CREAT|O_EXCL, 0644);
	if (fd < 0) {
		if (EEXIST == errno) { //file exist.
			printf("file exist!\n");
			fd = open("test.c", O_RDWR|O_APPEND);
		} else {
			perror("open failed!");
			return -1;
		}

	} 
	
	// handle the file
	//...
	
	if (fd > 0 )
		close(fd);

	return 0;
}
