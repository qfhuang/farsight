#include "sem_common.h"

int main(int argc, char *argv[])
{
	// 构建semIPC对象
	key_t key;
	int semid;
	pid_t pid;
	int ret = -1;

	key = ftok(".", 'a');
	if(key < 0)
	{
		perror("ftok");
		exit(1);
	}

	semid = semget(key, 1, IPC_CREAT|0644);
	if(semid < 0)
	{
		perror("setmget");
		exit(1);
	}
	system("ipcs -a");
	
	ret = init_sem(semid, 0, 1);		
	if(ret < 0)
		exit(1);

	pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}	
	
	if(pid == 0)
	{
		printf("--------in child--------\n");
		//先让子进程对进行操作
		sem_p(semid, 0);
		printf("child do first, pls wait\n");
		sleep(8);
		sem_v(semid, 0);
	
	}
	if(pid > 0)
	{
		sleep(2);		
		printf("--------in parent--------\n");
		// 父进程必须等子进程释放sem才能继续往下走
		sem_p(semid, 0);
		printf("parent start to run\n");
		sem_v(semid, 0);

		del_sem(semid, 0);
		system("ipcs -a");
	}

	return 0;
}
