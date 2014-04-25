#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
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
		do {
	         	ret = read(fd, buff, BUFSIZ-1);
		} while( (ret <0) && (EINTR == errno) ); 
	
		buff[BUFSIZ -1] = '\0';
		
		if (ret > 0) {
			printf("%s", buff);
		} else {
			break;		
		}			
	}
	//至此文件指针到了末尾

	//把文件指针调整到文件头
	printf("-------lseek funcation demo ------\n");
	lseek(fd, 0, SEEK_SET);
	
	bzero(buff, BUFSIZ);
	//读取数据用于演示lseek
	do {
            ret = read(fd, buff, BUFSIZ-1);
        } while( (ret <0) && (EINTR == errno) );
	buff[BUFSIZ -1] = '\0';

	printf("after lseek\n %s\n", buff);
			
		
	if (fd > 0 )
		close(fd);

	return 0;
}
