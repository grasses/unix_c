//
//  chdir.cpp
//  unix_c
//
//  Created by homeway on 28/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <unistd.h>

int main(void) {
	char* path;
	if (getcwd(path, 1024) < 0) {
		err_ret("getcwd error\n");
	} else {
		printf("curr cwd = %s\n", path);
	}
	
	printf("=> chdir /\n");
	if (chdir("/") < 0) {
		err_ret("chdir / error\n");
	}

	if (getcwd(path, 1024) < 0) {
		err_ret("getcwd error\n");
	} else {
		printf("curr cwd = %s\n", path);
	}	
}

