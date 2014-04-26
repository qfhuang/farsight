#ifndef __SEM_COMMON_H__

#define __SEM_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


union semun{
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
				    (Linux-specific) */
};

int init_sem(int semid, int semnth, int val);
int del_sem(int semid, int semnth);
int sem_p(int semid, int semth);
int sem_v(int semid, int semth);



#endif
