#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	pid_t pid[5];
	int i = 0;
	for (; i < 5; ++i) {
		pid[i] = fork();
		if (pid[i] < 0) {
			perror("fork error\n");
			exit(1);
		} else if (pid[i] == 0) {
			printf("=> child: pid = %d, ppid = %d\n", getpid(), getppid());
			break;
		} else {
			printf("=> parent: pid = %d, cid = %d\n", getpid(), pid[i]);
		}
	}	
	
	if (i == 5) {	// parent
		sleep(5);
		waitpid(-1, NULL, WNOHANG);
		while(1);
	} else {
		sleep(i);
		printf("=> dying child: %dth child, pid = %d, ppid = %d\n", i, getpid(), getppid());
	}


	return 0;
}
