#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void signal_func(int v) {
	printf("call singal func, sig id = %d\n", v);
}

int main() {
	if(signal(SIGALRM, signal_func) < 0) {
		perror("signal error:");
		exit(1);
	}

	struct itimerval new, old;
	new.it_value.tv_sec = 2;
	new.it_value.tv_usec = 0;

	new.it_interval.tv_sec = 1;
	new.it_interval.tv_usec = 0;

	if (setitimer(ITIMER_REAL, &new, &old) < 0) {
		perror("setimer error:");
		exit(1);
	}
	
	while(1);
	return 0;
}
