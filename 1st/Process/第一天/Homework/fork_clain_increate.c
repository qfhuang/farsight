#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	pid_t pid;
	int i;
	
	for(i = 0; i < 10; i++) {
		pid = fork();
		if(pid > 0) 
			break;
	}

	printf("parent getpid = %d\n",getpid());
	return 0;
}
