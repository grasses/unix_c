#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int debug = 1;

void sig_handler(int sid) {
	if (debug) 
		printf("----------catch----------\n");
}

unsigned int mysleep(int sec) {
	struct sigaction sc, old;
	sc.sa_handler = sig_handler;
	sc.sa_flags = 0;
	sigemptyset(&sc.sa_mask);
	
	int ret = sigaction(SIGALRM, &sc, &old);
	if (ret < 0) {
		perror("sigaction error:");
		exit(1);
	}

	alarm(sec);
	ret = pause();
	if (ret == -1 && errno == EINTR) {
		if (debug) 
			printf("----------pause----------\n");
	}
	ret = alarm(0);
	sigaction(SIGALRM, &old, NULL);
	return ret;
}

int main() {
	while(1) {
		printf("---------->\n");
		mysleep(2);
	}
	return 0;
}
