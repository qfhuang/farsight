#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	pid_t pid;
	int i;
	
	for(i = 0; i < 10; i++) {
		pid = fork();
		if(pid == 0) {
			printf("child getpid = %d\n",getpid());
			exit(0);
		}
	}
	
	for(i = 0; i < 10; i++) {
		wait(NULL);
	}
	printf("parent getpid = %d\n",getpid());
	return 0;
}
