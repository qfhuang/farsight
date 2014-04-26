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
    struct msg info = {12, "msg_info", 'R'};

    ret = access("myfifo", F_OK);
    if(ret != 0)
    {
	//创建管道
	ret = mkfifo("myfifo", 0666);
	if(ret < 0)
	{
	    perror("mkfifo");
	    exit(1);
	}
    }
    //打开管道
    printf("open之前!\n");
    fd = open("myfifo", O_WRONLY|O_NONBLOCK);
    if(fd < 0)
    {
	perror("open");
	exit(1);
    }
    printf("open之后!\n");

    //从管道中读写数据
  //  while(1)
    {
//	fgets(buf, 1024, stdin);
//	if(strncmp(buf, "quit", 4) == 0)
//		break;
	write(fd, &info, sizeof(struct msg));
    }
    sleep(10);
    close(fd);
    return 0;

}
