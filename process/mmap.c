#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(void) {
	int fd = open("out.mmap.txt", O_RDWR|O_CREAT, 0644);
	if (fd < 0) {
		perror("open error:");
		exit(1);
	}

	char ptr[1024] = "I write it\n";
	int len = ftruncate(fd, strlen(ptr));
	
	char *p = mmap(NULL, strlen(ptr), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap error:");
		exit(1);
	}
	strcpy(p, ptr);
	int ret = munmap(p, strlen(ptr));
	if (ret < 0) {
		perror("munmap error:");
		exit(1);
	}
	close(fd);
}
