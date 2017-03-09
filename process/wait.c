#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork error\n");
		exit(1);
	} else if(pid == 0) {
		printf("=> child\n");
		sleep(12);
		printf("=> child: going to die\n");
	} else {
		printf("=> parent\n");
		int i = 15;
		while (i-- > 0) {
			sleep(1);
			printf("=> parent: pid = %d, child id = %d\n", getpid(), pid);
		}

		printf("=> parent: wait()\n");
		int stat;
		pid_t wpid = wait(&stat);
		if (wpid < 0) {
			perror("wait error\n");
			exit(1);
		}

		if (WIFEXITED(stat)) {
			printf("=> parent: child exit, id = %d\n", WEXITSTATUS(stat));
		}

		if (WIFSIGNALED(stat)) {
			printf("=> parent: child kill, signal id = %d\n", WTERMSIG(stat));
		}
	}

	return 0;
}
