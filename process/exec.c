#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	pid_t pid = fork();

	if (pid < 0) {
		perror("fork error\n");
		exit(1);
	} else if(pid == 0) {
		printf("=> child\n");
		
		printf("=> execv()\n");
		char* xargv[]  = {"ls", "-l", "exec", NULL};
		execv("/bin/ls", xargv);

	} else {
		sleep(1);
		printf("\n=> parent\n");

		printf("=> execlp()\n");
		execlp("ls", "ls", "-l", NULL);
	}
	return 0;
}
