#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int fd = -1, ret = -1;
	char buff[BUFSIZ];

	fd = open("hole", O_WRONLY|O_CREAT|O_EXCL, 0644);
	if (fd < 0) {
		if (EEXIST == errno) { //file exist.
			printf("file exist!\n");
			fd = open("hole", O_RDWR|O_APPEND);
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

	//生成空洞
	printf("-------hole file funcation demo ------\n");
	lseek(fd, 1024*1024, SEEK_END);
	
	//写数据用于演示lseek
	bzero(buff, BUFSIZ);
	strcpy(buff, "This is a hole file");	
	do {
            ret = write(fd, buff, strlen(buff));
        } while( (ret <0) && (EINTR == errno) );	

//	sync(); //刷新
	fsync(fd);

	printf("after lseek\n");
			
		
	if (fd > 0 )
		close(fd);

	return 0;
}
