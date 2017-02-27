#include "src/apue.h"
#include <errno.h>

static void sigh_hup(int signo)
{
	printf("sigh up received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name)
{
	printf("%s: pid = %ld ppid = %ld pgrp = %ld tpgrp = %ld\n", name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(void)
{
    char c;
    pid_t pid;
    pr_ids("parent");
    
    if((pid = fork()) < 0)
    {
        //err_sys("fork error");
    } else if(pid > 0) {
        //parent
        sleep(1);
    } else {
        pr_ids("child");
        signal(SIGHUP, sigh_hup);
        kill(getpid(), SIGTSTP);
        pr_ids("child");
        if(read(STDIN_FILENO, &c, 1) != 1)
        {
            printf("\nread error %d on controlling tty\n", errno);
        }
    }
    return 0;
}
