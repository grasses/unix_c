#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void signal_child_catch(int sid) {
	int status;
	pid_t pid;
	while ((pid = waitpid(0, &status, WNOHANG)) > 0) {
		if (WIFEXITED(status)) {
			printf("child: singal pid = %d exit\n", pid);
		} else if (WIFSIGNALED(status)) {
			printf("child: pid = %d, cancel signal = %d\n", pid, WTERMSIG(status));
		}
	}
}

int main() {
	int i = 0;
	pid_t pid;
	for (i = 0; i < 5; ++i) {
		if((pid = fork()) == 0) {
			break;
		} else if (pid < 0) {
			perror("fork error:");
			exit(1);
		}
	}

	if (pid > 0) {
		// parent
		struct sigaction sa;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = signal_child_catch;
		sigaction(SIGCHLD, &sa, NULL);
	
		while (1) {
			// printf("parent: pid = %d\n", getpid());
			sleep(1);
		}
	} else if (pid == 0) {
		// child
		printf("child: i = %d pid = %d\n", i + 1, getpid());
		sleep(1);
		return i + 1;
	}
	return 0;
}
