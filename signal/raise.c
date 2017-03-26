#include <stdio.h>
#include <signal.h>

int main() {
	raise(SIGKILL);
	return 0;
}
