#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    pid_t pid;
    int max_fd;
    int i;

    //第一次fork
    pid = fork();
    if(pid > 0)
	exit(0);
    //调用setsid()，创建新的会话
    setsid();
    //第二次fork
    pid = fork();
    if(pid > 0)
	exit(0);
    //调用setpgrp，创建新的进程组
    setpgrp();
    //忽略信号的影响
    signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    //关闭所有打开的文件描述符
    max_fd = sysconf(_SC_OPEN_MAX);
    for (i = 0; i < max_fd;i++)
	close(i);
    //消除umask的影响
    umask(0);
    //改变进车功能当前工作目录
    chdir("/");
    //对标准IO进行重定向
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
//    open("/dev/null", O_RDWR);
//===============以下为守护进程======
     int fd;
     int fd_err;
     i = 100;
     char buf[] = "This is daemon test!\n";
     fd = open("daemon.dat", O_RDWR|O_APPEND|O_CREAT,0666);
     if(fd < 0)
     {
	 perror("open");
	 exit(1);
     }
     while(i--)
     {
	 write(fd, buf, strlen(buf));
	 sleep(1);
     }

    close(fd);

}
