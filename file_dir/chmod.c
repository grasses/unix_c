//
//  chmod.cpp
//  unix_c
//
//  Created by homeway on 27/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		err_ret("Usage: %s filename", argv[0]);
	}
	char cmd[128];
	sprintf(cmd, "ls -l %s", argv[1]);
	
	printf("%s: file permission:\n", argv[1]);
	system(cmd);
	if (chmod(argv[1], (S_IRWXU|S_IRGRP|S_IROTH)) < 0) {
		err_sys("%s: chmod error", argv[1]);
		exit(1);
	} else { 
		printf("\n%s: chmod => -rwxr--r--\n", argv[1]);
	}
	system(cmd);

}
