//
//  getgid.c
//  unix_c
//
//  Created by homeway on 02/03/2017.
//  Copyright © 2017 homeway. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>

int main(int argc, char** argv) {
	if (argc != 2) {
        printf("Usage: %s *username", argv[0]);
        return 0;
    }
    
    struct passwd* pwd;
    struct group *grp;
    
    if((pwd = getpwnam(argv[1])) == NULL) {
        printf("getpwnam error\n");
        return 0;
    }
    
    if((grp = getgrgid(pwd->pw_gid)) == NULL) {
        printf("getgrgid error\n");
        return 0;
    }
    printf("gid = %d, name = %s, passwd = %s\n", grp->gr_gid, grp->gr_name, grp->gr_passwd);
    return 0;	
}
