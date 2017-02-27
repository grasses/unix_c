//
//  4.3.cpp
//  unix_c
//
//  Created by homeway on 27/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include <stdio.h>
#include "apue.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: %s filepath\n", argv[0]);
		exit(0);
	}
	struct stat buff;
	char ptr[512];
	for (int i = 1; i < argc; ++i) {
		if (lstat(argv[i], &buff) < 0) {
			printf("last(%s) error", argv[i]);
		}
		if (S_ISREG(buff.st_mode)) 
			sprintf(ptr, "%s: regular file\n", argv[i]);
		else if (S_ISDIR(buff.st_mode))
			sprintf(ptr, "%s: directory\n", argv[i]);
		else if (S_ISCHR(buff.st_mode))
			sprintf(ptr, "%s: character special\n", argv[i]);
		else if (S_ISBLK(buff.st_mode))
			sprintf(ptr, "%s: block special\n", argv[i]);
		else if (S_ISFIFO(buff.st_mode))
			sprintf(ptr, "%s: FIFO file\n", argv[i]);
		else if (S_ISLNK(buff.st_mode))
			sprintf(ptr, "%s: link file\n", argv[i]);
		else if (S_ISSOCK(buff.st_mode))
			sprintf(ptr, "%s: sock", argv[i]);
		printf("%s", ptr);
	}	
	return 0;
}
