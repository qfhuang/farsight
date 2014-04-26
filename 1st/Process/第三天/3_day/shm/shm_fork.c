#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define WRITE_FLAG "WRITTEN"
#define SHM_SIZE 4096

int main(int argc, char *argv[])
{
	int ret = -1;
	key_t key;
	int shmid;
	char *shmaddr;
	pid_t pid;
	char buf[SHM_SIZE];

	// 构建shm IPC对象， 在亲属关系的进程中用IPC_PRIVATE
	shmid = shmget(IPC_PRIVATE, SHM_SIZE,  IPC_CREAT | 0644);
	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	
	// 在此fork两个进程，父进程输入，子进程负责输出
       // 父子进程必须都要将shm映射到自己的空间中
	pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	
	if(pid == 0)
	{
		printf("in child to read shm\n");
		// 将shm映射到自己空间
		shmaddr = shmat(shmid, NULL, 0);
		if(shmaddr == (char *)-1)	
		{
			perror("shmaddr");
			exit(1);
		}

		//在该空间中可以之际操作shm，读数据
		while(strncmp(shmaddr, WRITE_FLAG, strlen(WRITE_FLAG)) != 0)
		{
			printf("waiting data.........\n");
			sleep(3);
		}
		snprintf(buf, SHM_SIZE, "%s", shmaddr+strlen(WRITE_FLAG));
		printf("^_^ got a data : %s\n", buf);
		// 解除映射
		ret = shmdt(shmaddr);
		if(ret < 0)
		{
			perror("shmat");
			exit(1);
		}


	}
	if(pid > 0)
	{
		printf("in parent to write shm\n");
		shmaddr = shmat(shmid, NULL, 0);
		if(shmaddr == (char *)-1)	
		{
			perror("shmaddr");
			exit(1);
		}

		system("ipcs -m");
		
		sleep(6);
		
		snprintf(buf, SHM_SIZE, "%s---%s", WRITE_FLAG, "hello shm from parent");
		memcpy(shmaddr, buf, strlen(buf));

		// 等待子进程退出
		waitpid(pid, NULL, 0);
		printf("child has gone\n");
		// 解除映射
		ret = shmdt(shmaddr);
		if(ret < 0)
		{
			perror("shmat");
			exit(1);
		}

		// 删除IPC对象
		ret = shmctl(shmid, IPC_RMID, NULL);
		if(ret < 0)
		{
			perror("shctl");
			exit(1);
		}

		system("ipcs -m");

	}
	
	return 0;
}
