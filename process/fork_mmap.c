#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main(void) {
	const char fname[64] = "out.fork_map.txt";
	int fd = open(fname, O_RDWR|O_CREAT, 0644);
	if (fd < 0) {
		perror("open error:");
		exit(1);
	}
	
	char ptr[1024] = "write message\n";
	int len = ftruncate(fd, strlen(ptr));
	char *p = mmap(NULL, strlen(ptr), PROT_READ|PROT_WRITE, MAP_SHARED,  fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap error:");
		exit(1);
	}
	unlink(fname);	// not unlink()?
	close(fd);
	
	pid_t pid = fork();
	if (pid == 0) {	// child
		strcpy(p, "<=============hello child=============>");
		printf("=> child: change to: *p = %s\n", p);
	} else if (pid > 0) {
		sleep(1);
		printf("=> parent: read *p = %s\n", p);
	} else {
		perror("fork error:");
		exit(1);
	}

	return 0;
}
