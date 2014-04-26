#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
 #include <sys/shm.h>

#define SHM_SIZE 4096

int main(int argc, char *argv[])
{
	int ret = -1;
	key_t key;
	int shmid;
	char *shmaddr;

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

	system("ipcs -m");
	

	ret = shmdt(shmaddr);
	if(ret < 0)
	{
		perror("shmat");
		exit(1);
	}

	ret = shmctl(shmid, IPC_RMID, NULL);
	if(ret < 0)
	{
		perror("shctl");
		exit(1);
	}

	system("ipcs -m");
	
	return 0;
}
