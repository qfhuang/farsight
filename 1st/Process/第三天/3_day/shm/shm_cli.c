#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

#define WRITE_FLAG "WRITTEN"
#define SHM_SIZE 4096

int main(int argc, char *argv[])
{
	int ret = -1;
	key_t key;
	int shmid;
	char *shmaddr;
	char buf[SHM_SIZE];

	key = ftok(".", 'a');
	if(key < 0)
	{
		perror("ftok");
		exit(1);
	}
	// 构建shm IPC对象
	shmid = shmget(key, SHM_SIZE,  IPC_CREAT | 0644);
	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr == (char *)-1)	
	{
		perror("shmaddr");
		exit(1);
	}

	printf("---------in client---------------\n");
	system("ipcs -m");
	 
	//在该空间中可以之际操作shm，读数据
	while(strncmp(shmaddr, WRITE_FLAG, strlen(WRITE_FLAG)) != 0)
	{
		printf("in client : waiting data.........\n");
		sleep(3);
	}
	snprintf(buf, SHM_SIZE, "%s", shmaddr+strlen(WRITE_FLAG));
	printf("in client ^_^ got a data : %s\n", buf);



	// 解除映射
	ret = shmdt(shmaddr);
	if(ret < 0)
	{
		perror("shmat");
		exit(1);
	}
	system("ipcs -m");
	
	return 0;
}
