//
//  mkdir.cpp
//  unix_c
//
//  Created by homeway on 27/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

#include "apue.h"
#include "error.c"
#include <sys/stat.h>

int main(int argc, char** argv) {
	if (argc == 1) {
		err_quit("Usage: %s pathname", argv[0]);
	}
	
	char cmd[512];
	for (int i = 1; i < argc; ++i) {
		if (mkdir(argv[i], (RWRWRW)) < 0) {
			err_ret("%s: mkdir error", argv[i]);
		} else {
			printf("%s: mkdir success\n", argv[i]);
			sleep(1);
			sprintf(cmd, "ls -l %s", argv[i]);
			system(cmd);
		}
	}

	for (int i = 1; i < argc; ++i) {
		if (rmdir(argv[i]) < 0) {
			err_ret("%s: rmdir error", argv[i]);
		} else {
			printf("%s: rmdir success\n", argv[i]);
			sleep(1);
			sprintf(cmd, "ls -l %s", argv[i]);
			system(cmd);
		}
	}
}
