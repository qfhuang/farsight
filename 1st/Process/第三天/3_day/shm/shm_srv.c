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

	printf("---------in srv---------------\n");
	system("ipcs -m");
	
	 sleep(6);

	 snprintf(buf, SHM_SIZE, "%s---%s", WRITE_FLAG, "hello shm from parent");
	 memcpy(shmaddr, buf, strlen(buf));
	 printf("write ok\n");

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
	
	return 0;
}
