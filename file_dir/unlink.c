//
//  unlink.cpp
//  unix_c
//
//  Created by homeway on 27/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
	char fname[128] = "tmpfile";
	if (open("tmpfile", O_RDWR) < 0)
		err_sys("%s: open error", fname);
	if (unlink("tmpfile") < 0)
		err_sys("%s: unlink error", fname);
	printf("%s unlinked, sleep 15 seconds\n", fname);
	sleep(15);
	printf("done\n");
	return 0;	
}

