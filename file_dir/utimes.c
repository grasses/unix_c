//
//  umask.cpp
//  unix_c
//
//  Created by homeway on 27/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <utime.h>

int main(int argc, char** argv) {
	int fd;
	struct stat buff;
	struct utimbuf time;

	if (argc == 1) {
		err_quit("Usage: %s pathname1 pathname2 ...\n", argv[0]);
	} 

	for (int i = 1; i < argc; ++i) {
		if (stat(argv[i], &buff) < 0) {
			err_ret("%s: stat error", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
			err_ret("%s: open file error", argv[i]);
		}
		time.actime = buff.st_atime;
		time.modtime = buff.st_mtime;
		if (utime(argv[i], &time) < 0) {
			err_ret("%s: futimens error", argv[i]);
		}
		close(fd);
	}
}
