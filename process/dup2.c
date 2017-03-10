#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void) {
	int fd = open("out.ps.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (fd < 0) {
		perror("open file error\n");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	
	char* argv[] = {"ps", "aux", NULL};
	execv("/bin/ps", argv);

	return 0;
}
