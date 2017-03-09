#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void) {
	char fname[64] = "/dev/zero";
	int fd = open(fname, O_RDWR);

	int *p = (int*) mmap(NULL, 4094, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
	if (p == MAP_FAILED) {
		perror("mmap error:");
		exit(1);
	}

	int var = 1024;
	printf("=> origin: var = %d\n", var);

	pid_t pid = fork();
	if (pid == 0) {
		*p = 12345678;
		var = 2048;
		printf("=> child: *p = %d, var = %d\n", *p, var);
	} else if (pid > 0) {
		sleep(1);
		printf("=> parent: *p = %d, var = %d\n", *p, var);
	} else {
		perror("fork error:");
		exit(1);
	}

	return 0;
}
