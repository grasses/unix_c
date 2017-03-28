#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int cnt = 0, flag = 0;
// 进程竞态测试

void parent_sig_catch(int num) {
	printf("I`m parent, pid = %u, cnt = %d\n", getpid(), cnt);
	cnt += 2;
	flag = 1;
	sleep(1);
}

void child_sig_catch(int num) {
	printf("I`m parent, pid = %u, cnt = %d\n", getpid(), cnt);
	cnt += 2;
	flag = 1;
	sleep(1);
}

int main() {
	struct sigaction sc;
	pid_t pid = fork();
	if (pid > 0) {
		// parent
		cnt = 1;
		sleep(1);

		sc.sa_flags = 0;
		sigemptyset(&sc.sa_mask);
		sc.sa_handler = parent_sig_catch;
		sigaction(SIGUSR2, &sc, NULL);

		parent_sig_catch(0);
		while (1) {
			if (flag == 1) {
				kill(pid, SIGUSR1);
				flag = 0;
			}
		}
	} else if (pid == 0) {
		// child
		cnt = 2;
		sc.sa_flags = 0;
		sigemptyset(&sc.sa_mask);
		sc.sa_handler = child_sig_catch;
		sigaction(SIGUSR1, &sc, NULL);

		while (1) {
			if (flag == 1) {
				kill(getppid(), SIGUSR2);
				flag = 0;
			}
		}
	} else {
		perror("fork error:");
		exit(1);
	}
	return 0;
}
