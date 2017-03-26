#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_func(int sid) {
	printf("catch signal id = %d\n", sid);
}

typedef void (*sighandler_t) (int);

int main() {
	sighandler_t handler = signal(SIGINT, sig_func);
	if (handler == SIG_ERR) {
		perror("signal error:");
		exit(1);
	}

	while(1);
	// test => ctrl + c
	// exit => ctrl + z
	return 0;
}
