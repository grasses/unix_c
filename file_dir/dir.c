//
//  dir.cpp
//  unix_c
//
//  Created by homeway on 28/02/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include "apue.h"
#include "error.c"
#include <dirent.h>

int dir_type(const char* pathname) {
	struct stat stat_buff;
	if (stat(pathname, &stat_buff) < 0) {
		err_ret("%s: stat error", pathname);
		return -1;
	}
	if (S_ISDIR(stat_buff.st_mode)) {
        return 1;
    }
    if (S_ISREG(stat_buff.st_mode)) {
        return 2;
    }
    return 0;
}

void dfs(char* pathname) {
	DIR* dir;
	struct dirent* dire;
	char next[1024];
	if ((dir = opendir(pathname)) == NULL)	{
		err_ret("%s: opendir error", pathname);
		return;
	}
	while ((dire = readdir(dir)) != NULL) {
		sprintf(next, "%s/%s", pathname, dire->d_name);
		if (strcmp(dire->d_name, ".DS_Store") == 0 || strcmp(dire->d_name, "..") == 0 || strcmp(dire->d_name, ".") == 0) {
            continue;
        }
		int ret_stat = dir_type(next);
		switch (ret_stat) {
			case 1:
				printf("Dir => %s\n", next);
				dfs(next);
				break;
			case 2:
				printf("File => %s\n", next);
				break;
		}
	}
}

int main(int argc, char** argv) {
	if (argc == 1) {
		err_quit("Usage: %s pathname\n", argv[0]);
	}
	dfs(argv[1]);	
}
