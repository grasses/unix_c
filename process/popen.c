#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char** argv) {	
	char buffer[1024];
	for(int i = 1; i < argc; i++ ) {
		strcat( buffer, argv[i] );
	        strcat(buffer, " ");
	}

	FILE *st = popen(buffer, "w");
	if (!st) {
		perror("popen error:");
		exit(1);
	}
	
	char tmp[1024]; 
	while (fgets(tmp, sizeof(tmp), st)) {
		if (tmp[strlen(tmp) - 1] == '\n') {
			tmp[strlen(tmp) - 1] = '\0';
		}
	}

	if (pclose(st)) {
		perror("pclose error:");
		exit(1);
	}
	
	return 0;
}
