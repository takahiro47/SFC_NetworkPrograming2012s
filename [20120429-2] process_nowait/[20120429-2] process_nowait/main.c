//
//  main.c
//  [20120429-2] process_nowait
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    pid_t ret;
    
    ret = fork();
    if (ret == 0) {
        sleep(3); //子プロセスのみ3秒待っているので、親プロセスが先に終了する。
        printf("This is a child process\n");
    } else if (ret > 0) {
        printf("This is a parent process\n");
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

