#include "sem_common.h"

// 设置sem的初始值, sem是第几个，如果有多个，是从0开始
// val 为信号量的初始值
int init_sem(int semid, int semnth, int val)
{
	int ret = -1;
	union semun sem_u;
	
	sem_u.val = val;
	ret = semctl(semid, semnth, SETVAL, sem_u);
	if(ret < 0)
	{
		perror("semctl init");
		return -1;
	}
	
	return ret;
}
// 删除sem集，第二个参数会被忽略不算
int del_sem(int semid, int semnth)
{
	int ret = -1;
	union semun sem_u;
	
	ret = semctl(semid, semnth, IPC_RMID, sem_u);
	if(ret < 0)
	{
		perror("semctl del");
		return -1;
	}
	
	return ret;
		
}


int sem_p(int semid, int semth)
{
	int ret = -1;
	struct sembuf sem_b;

	sem_b.sem_num = semth;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;

	ret = semop(semid, &sem_b, 1);
	if(ret < 0)
	{
		perror("semop p");
		return -1;
	}
	return ret;
}


int sem_v(int semid, int semth)
{	
	int ret = -1;
	struct sembuf sem_b;
	sem_b.sem_num = semth;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;

	ret = semop(semid, &sem_b, 1);
	if(ret < 0)
	{
		perror("semop p");
		return -1;
	}
	return ret;
}

