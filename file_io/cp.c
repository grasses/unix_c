//
//  cp.c
//  unix_c
//
//  Created by homeway on 02/03/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#define BUFFSIZE 1024

int main(int argc, char** argv) {
	if (argc != 3) {
		err_quit("Usage: %s from to", argv[0]);
	}
	char buff[BUFFSIZE];	
	
	int fd1, fd2, read_byte, write_byte;
	if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
		err_quit("%s: open file error", argv[1]);
	}
	if ((fd2 = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0) {
		err_quit("%s: create file error", argv[2]);
	}
	
	while ((read_byte = read(fd1, buff, BUFFSIZE)) != 0) {
		if (read_byte == -1 && (errno != EINTR)) {
			err_quit("%s: read buff error", argv[1]);
		} else if (read_byte > 0) {
			write_byte = write(fd2, buff, read_byte);
			if (write_byte == -1) {
				err_quit("%s: write buff error", argv[2]);
			}
		}
	}
	close(fd1);
	close(fd2);
	return 0;	
}
