//
//  main.c
//  [20120429-1] create_proc
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

/*
 fork()     :子プロセスを生成し、親プロセスのアドレス空間を丸ごと複製して子プロセスのアドレス空間として割り当てる。
 (テキスト領域、データ領域、ヒープ領域、スタック領域etc)
 エラーの戻り値は-1。成功した場合は親プロセスの場合は子プロセスのIDを、子プロセスの場合は0が返される
 getpid()   :呼び出し元のプロセスIDを返す
 getppid()  :呼び出し元の親プロセスIDを返す
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    pid_t ret;
    int i;
    
    printf("[BEFORE FORK]\n Process ID: %d\t Parent Process ID: %d\n\n", getpid(), getppid());
    
    ret = fork(); //ここで子プロセスが生成され、ここより先のコードは子と親のプロセスそれぞれで別々に実行される
    srand(time(NULL));
    printf("[AFTER FORK]\n Process ID: %d\t Parent Process ID: %d\n", getpid(), getppid());
    printf("[id=%d] Return Values of Fork: %d\n", getpid(), ret);
    printf("\n");
    
    sleep(1);
    
    for (i = 0; i < 10; i++) {
        printf("(%d) for loop i=%d\n", getpid(), i);
        usleep(rand() % 3);
    }
    if (ret == 0) {
        printf("(%d) End the child process\n", getpid());
    } else if (ret > 0) {
        printf("(%d) End the parent process\n", getpid());
    } else {
        perror("ERROR!");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

