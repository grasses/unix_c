//
//  4.3.cpp
//  unix_c
//
//  Created by homeway on 27/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s filepath\n", argv[0]);
		exit(0);
	}
	if (access(argv[1], R_OK) < 0)
		printf("%s: access error\n", argv[1]);
	else
		printf("%s: access ok\n", argv[1]);
	
	if (open(argv[1], O_RDONLY) < 0)
		printf("%s: open error\n", argv[1]);
	else 
		printf("%s: open successfuly\n", argv[1]);
	return 0;
}
