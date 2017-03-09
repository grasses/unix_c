#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

struct user {
	char name[32], fio[512];
	int uid, age;
};

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_CREAT|O_RDWR, 0644);
	if (fd < 0) {
		printf("open error:");
		exit(1);
	}
	ftruncate(fd, sizeof(struct user));
	struct user ptr = {"homeway", "homeway.me"};
	ptr.uid = 1;
	ptr.age = 24;
	
	char *p = mmap(NULL, sizeof(struct user), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap error:");
		exit(1);
	}
	close(fd);
	
	int cnt = 10;
	while(1) {
		printf("=> mmp_w: write uid = %d, name = %s, fio = %s, age = %d\n", ptr.uid, ptr.name, ptr.fio, ptr.age);
		memcpy(p, &ptr, sizeof(struct user));
		++ptr.uid;
		sleep(1);
	}
	munmap(p, sizeof(struct user));
	return 0;
}
