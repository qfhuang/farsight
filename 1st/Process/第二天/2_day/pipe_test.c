#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>


int main(void)
{
    pid_t pid;
    int fd[2];
    int ret;
    char buf[100];

    //创建管道
    ret = pipe(fd);
    if(ret < 0)
    {
	perror("pipe");
	exit(1);
    }
    pid = fork();
    if(pid == 0)
    {
	//子进程向管道中写数据
	//关闭读端
	close(fd[0]);
	while(1)
	{
	    printf("请输入要传给父进程的数据\n");
	    fgets(buf, 1024, stdin);
	    if(strncmp(buf, "quit", 4) == 0)
	    {
		write(fd[1], buf, strlen(buf));
		break;
	    }
	    write(fd[1], buf, strlen(buf));
	}   
	close(fd[1]);
	exit(0);
    }
    if(pid > 0)
    {
	//父进程从管道中读数据
	//关闭写端
	close(fd[1]);
	while(1)
	{
	    sleep(10);
	    ret = read(fd[0], buf, 20);
	    if(strncmp(buf, "quit", 4) == 0)
		break;
	    buf[ret] = '\0';
	    printf("从子进程读取的数据为: %s", buf);
	}
	close(fd[0]);
    }

    return 0;

}
