//
//  main.c
//  [20120429-5] proc_exec
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    pid_t pid;
    int status;
    
    printf("Exec ps program...\n");
    
    pid = fork();
    if (pid == 0) { //子プロセスへの命令
        execlp("ps", "ps", "-la", NULL);
    } else if (pid > 0) {
        wait(&status); //子プロセスの終了を待機
        printf("done.\n");
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

