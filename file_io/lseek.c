//
//  lseek.cpp
//  unix_c
//
//  Created by homeway on 28/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char** argv) {
	if (argc == 1) {
		err_quit("Usage: %s pathname", argv[0]);
	}
	int fd;
	if ((fd = creat(argv[1], FILE_MODE)) < 0) {
		err_sys("create file %s error", argv[1]);
	}

	char buff1[11] = {"1234567890"};
	char buff2[11] = {"abcdefghij"};

	if (write(fd, buff1, 10) != 10) {
		err_sys("write %s error", argv[1]);
	}

	if (lseek(fd, 1024, SEEK_SET) < 0) {
		err_sys("lseek %s error", argv[1]);
	}

	if (write(fd, buff2, 10) != 10) {
		err_sys("write %s error", argv[1]);
	}

	char cmd[1024];
	sprintf(cmd, "od -c %s", argv[1]);
	system(cmd);
}
