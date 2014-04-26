#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

struct msg
{
    short id;
    char name[20];
    char flg;
};

int main(void)
{
    int ret;
    int fd;
    char buf[100];
    struct msg read_info;

    //打开管道
    fd = open("myfifo", O_RDONLY);
    if(fd < 0)
    {
	perror("open");
	exit(1);
    }
    
    //从管道中读写数据
//    while(1)
    {
//	ret = read(fd, buf, 20);
	read(fd, &read_info, sizeof(struct msg));
//	buf[ret] = '\0';
	printf("id: %d name:%s flg = %c\n", read_info.id,\
		read_info.name, read_info.flg);
    }
    close(fd);
    return 0;

}
