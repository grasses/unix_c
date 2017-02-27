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
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char** argv) {
	char a[128] = "test_a.txt", b[128] = "test_b.txt";
	umask(0);
	if(creat(a, RWRWRW) < 0) {
		err_dump("%s: create file error", a);
	}
	umask(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	if (creat(b, RWRWRW) < 0) {
		err_dump("%s: create file error", b);
	}
	return 0;
}
