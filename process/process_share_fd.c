#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
	int fd[2], ret;
	pid_t pid = fork();
	
	char buff[1024] = "=====================wtf================";
	if (pid == 0) {
		fd[0] = open("share_fd.txt", O_WRONLY|O_CREAT);
		if (fd[0] < 0) {
			perror("=> parent: open error\n");
			exit(1);
		}
		ret = write(fd[0], buff, strlen(buff));
		if (ret > 0) {
			printf("=> parent: write ok...\n");
		}
		sleep(3);		// wait child read()
	} else if(pid > 0) {
		sleep(1);		// wait parent write()

		fd[1] = open("share_fd.txt", O_WRONLY|O_CREAT);
		if (fd[1] < 0) {
			perrro("=> child: open error\n");
			exit(1);
		}
		char cbuff[1024];
		ret = read(fd[1], mbuff, sizeof(cbuff));
		if (ret >= 0) {
			printf("=> child: read ok, info = %s\n", mbuff);
		}
	} else {
		perror("fork error\n");
		exit(1);
	}

	return 0;
}
