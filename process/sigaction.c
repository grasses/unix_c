#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sid) {
	printf("signal catch id = %d\n", sid);
}

int main() {
	struct sigaction sc;
	sc.sa_handler = handler;
	sigemptyset(&sc.sa_mask);
	sigaddset(&sc.sa_mask, SIGQUIT);
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
