//
//  getpwnam.c
//  unix_c
//
//  Created by homeway on 02/03/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <pwd.h>

struct passwd* getpwname(char* name) {
    struct passwd* ptr = NULL;
    setpwent();	// set to passwd file begin
    while((ptr = getpwent()) != NULL) {
        if (strcmp(name, ptr->pw_name) == 0) {
            break;
        }
    }
    endpwent(); // Don`t forget close pwd file
    return ptr;
}

int main(int argc, char** argv) {
	if (argc != 2) {
        printf("Usage: %s *pwdname", argv[0]);
        return 0;
    }
    struct passwd* ptr = getpwname(argv[1]);
    if(ptr != NULL) {
        printf("uid = %d\t      gid = %d\n", ptr->pw_uid, ptr->pw_gid);
        printf("Login = %s\t    Login class = %s\n", ptr->pw_name, ptr->pw_class);
        printf("Shell = %s\t    Directory = %s\n", ptr->pw_shell, ptr->pw_dir);
    } else {
        printf("Not found\n");
    }
	return 0;
}
