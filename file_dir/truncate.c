//
//  truncat.cpp
//  unix_c
//
//  Created by homeway on 27/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <stdio.h>
#include <unistd.h>

int str2int(char* s) {
	int sum = 0, len = (int)strlen(s);
	for (int i = 0; i < len; ++i) {
		sum = sum * 10 + s[i] - '0';
	}
	return sum;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		err_quit("Usage: %s pathname length", argv[0]);
	}
	
	char cmd[128];
	sprintf(cmd, "ls -l %s", argv[1]);
	
	system(cmd);
	if (truncate(argv[1], (off_t)(str2int(argv[2]))) < 0) {
		err_sys("%s: truncate(%s, %s) error", argv[1], argv[1], argv[2]);
	}
	system(cmd);
	return 0;
}
