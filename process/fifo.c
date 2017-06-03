#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
	int fd;
	if ((fd = mkfifo("out.fifo", 644)) < 0) {
		perror("mkfifo error:");
		exit(1);
	}
	
	pid_t pid = fork();
	if (pid > 0) {
	 	// parent write
		char pword[1024];
		strcpy(pword, "I`m parent, hello world\n");
		write(fd, pword, strlen(pword));
	} else if (pid == 0) {
		sleep(1);
		// child read
		char cword[1024];
		read(fd, cword, sizeof(cword));
		printf("=> child read: %s", cword);
	} else {
		perror("fork error:");
		exit(1);
	}
	return 0;
}
