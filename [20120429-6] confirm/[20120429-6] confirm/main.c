//
//  main.c
//  [20120429-6] confirm
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * ターミナルから./a.outで実行時、通常はCtr+Cで終了するが、
 * Ctr+Cの操作(SIGINT)を受け取った時のコマンドを作成することで、
 * 『本当に終了しますか？(y/n)』というメッセージが出て、yを押下した時のみ終了するように出来る。
 */

void stop();

int main(int argc, const char * argv[]) {
    signal(SIGINT, stop);
    while (1) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    
    return 0;
}

void stop() {
    int ans;
    printf("本当に終了しますか？(y/n)");
    ans = getchar();
    if (ans == 'y') {
        exit(EXIT_FAILURE);
    }
}