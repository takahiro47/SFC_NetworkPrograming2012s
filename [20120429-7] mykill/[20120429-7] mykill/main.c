//
//  main.c
//  [20120429-7] mykill
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {
    pid_t pid;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: mykill <process id>\n");
        exit(EXIT_FAILURE);
    }
    
    pid = atoi(argv[1]);
    if (kill(pid, SIGTERM) < 0) {
        perror("kill");
    }
    
    return 0;
}

