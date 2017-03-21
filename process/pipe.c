#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
	// fd[0] = read pipe; fd[1] = write pipe
	int fd[2], ret;
	ret = pipe(fd);
	if (ret < 0) {
		perror("pipe error\n");
		exit(1);
	}
	
	pid_t pid = fork();
	if (pid == 0) {
		printf("=> child\n");
		sleep(1);
		
		close(fd[1]); // child process close write
		char buff[1024];
		ret = read(fd[0], buff, sizeof(buff));
		if (ret >= 0) {
			printf("=> child: read = %s\n", buff);
		}
		close(fd[0]);
	
	} else if (pid > 0) {
		printf("=> parent\n");

		close(fd[0]); // parent process close read
		char buff[1024] = "123456789";
		ret = write(fd[1], buff, strlen(buff));
		if (ret >= 0) {
			printf("=> parent: write = %s\n", buff);
		}
		close(fd[1]);

		sleep(3);
	} else {
		perror("fork error\n");
		exit(1);
	}

	return 0;
}
