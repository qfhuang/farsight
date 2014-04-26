#include <stdio.h>
#include <unistd.h>


int main(void)
{
	char *arg[] = {"ls", "-al", NULL};
	char *env[] = {"USR = zhangsan", NULL};

	execl("/bin/ls", "ls", "-al", NULL);
	//execl("/home/farsight/lesson/1_day/mycp", "./mycp", "1.c", "2.c", NULL);
	//execv("/bin/ls", arg);
	//execle("/bin/ls", "ls", "-al", env);
	//execve("/bin/ls", arg, env);

	//execlp("ls", "ls", "-al", NULL);//系统对自动的从path路径中找可执行文件

	//execvp("ls" ,arg);

	return 0;
}
