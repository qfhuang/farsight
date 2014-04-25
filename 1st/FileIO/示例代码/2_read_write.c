#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int fd = -1, ret = -1;
	char buff[BUFSIZ];

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
	while(1) {
		ret = read(fd, buff, BUFSIZ-1);
		buff[BUFSIZ -1] = 0;
		if (ret > 0) {
			printf("%s", buff);
		} else if (ret  == 0 ) {
			printf(" file end!\n");
			break;
		} else {
			perror("\n\nRead file error!");
			return -1;
		}			
	}

		
	if (fd > 0 )
		close(fd);

	return 0;
}
