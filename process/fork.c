#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int pid = fork();
	
	if (pid == 0) {
		printf("=> child, pid = %u, ppid = %u\n", getpid(), getppid());

	} else if (pid > 0) {
		printf("=> parent, cid = %u, pid = %u, ppid = %u\n", pid, getpid(), getppid());
	} else {
		printf("fork() error\n");
		exit(0);
	}

	printf("xxxxxxxxxxxxxxxxxxxxx\n");
	
	return 0;
}
