//
//  main.c
//  [20120429-8] comm1
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/* prototypes */
void chop(char *);

/* variables */

/* main */
#pragma main
int main(int argc, const char * argv[]) {
    char str[256];
    int fd[2]; //fd[0]:パイプからの読み込み用ファイル記述子／fd[1]:書き込み用ファイル記述子
    pid_t ret;
    int status;
    
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    ret = fork();
    if (ret == 0) { //子プロセスへの命令
        read(fd[0], str, sizeof(str));
        printf("A child Process: My parent said, \"%s\"\n", str);
    } else if (ret == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else { //親プロセスへの命令
        printf("A parent process: input any string> ");
        fgets(str, sizeof(str), stdin);
        chop(str);
        write(fd[1], str, sizeof(str));
        wait(&status);
    }
    
    return 0;
}


/* ------------------------------------------------
 void chop(char *str)
 関数
 input  >> char *str :
 return >> 
 ------------------------------------------------- */
void chop (char *str) {
    str[strlen(str)-1] = '\0';
    return;
}




