#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

struct user{
	char name[32], fio[512];
	int uid, age;
};

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: %s filepath", argv[0]);
		exit(1);
	}	

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open error\n");
		exit(1);
	}
	// ftruncate(fd, sizeof(struct user));

	struct user *p = mmap(NULL, sizeof(struct user), PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap error:");
		exit(1);
	}
	close(fd);
	while(1) {
		printf("=> read(): uid = %d, name = %s, fin = %s, age = %d\n", p->uid, p->name, p->fio, p->age);
		sleep(1);
	}
	munmap(p, sizeof(struct user));

	return 0;
}
