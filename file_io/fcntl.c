//
//  fctnl.c
//  unix_c
//
//  Created by homeway on 02/03/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, const char** argv) {
	if (argc == 1) {
		err_quit("Usage: %s <descraption#>", argv[0]);
	}
	
	int value;
	if ((value = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
		err_sys("fcntl error for fd %d", atoi(argv[1]));
	}

	switch (value&O_ACCMODE) {
		case O_RDONLY:
			printf("read only\n");
			break;
		case O_WRONLY:
			printf("write only\n");
			break;
		case O_RDWR:
			printf("read && wirte\n");
			break;
		default:
			printf("unknow type\n");
			break;
	}
		
	if (value & O_APPEND)
		printf(", append");
	if (value & O_NONBLOCK)
		printf(", nonblicking");
	if (value & O_SYNC)
		printf(", synchronous write");
	
	printf("\n");


	return 0;
}
