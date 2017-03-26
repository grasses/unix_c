#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sid) {
	printf("signal catch id = %d, sleep(5)...\n", sid);
	sleep(3);
	printf("--------finish----------\n");
}

int main() {
	struct sigaction sc;
	sc.sa_handler = handler;
	sigemptyset(&sc.sa_mask);
	sigaddset(&sc.sa_mask, SIGINT);
	sc.sa_flags = 0;
	
	if(sigaction(SIGINT, &sc, NULL) < 0) {
		perror("sigaction error:");
		exit(1);
	}

	while(1);
	// test => ctrl + c
	// quit => ctrl + z
	return 0;
}
