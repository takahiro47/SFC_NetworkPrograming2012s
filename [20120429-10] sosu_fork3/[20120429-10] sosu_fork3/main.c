//
//  main.c
//  [20120429-10] sosu_fork3
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
#define R (0)
#define W (1)

/* main */
#pragma main
int main(int argc, const char * argv[]) {
    char tmp[100];
    int limit ,i, j, count = 0, *prime;
    
    int fd1[2], fd2[2]; //fd[R]:パイプからの読み込み用／fd[W]:書き込み用。fd1:親→子／fd2:子→親。
    pid_t ret;
    int status;
    
    /* 上限を指定 */
    printf("探索する上限の数： ");
    fgets(tmp, 100, stdin);
    limit = atoi(tmp) + 1; //上限の数(自身も含める)
    
    /* メモリ確保と初期化 */
    prime = (int*)malloc(sizeof(int)*limit);
    prime[0] = prime[1] = 0; //0,1は素数でない
    for(i=2; i<limit; i++) prime[i]=1; //全ての数に1を立てて初期化(1は素数, 0は合成数)
    
    if (pipe(fd1) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(fd2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    printf ( "[%d] pipe(1) -> Read(fd1[R]): %d, Write(fd1[W]): %d\n", (int) getpid(), fd1[R], fd1[W] );
    printf ( "[%d] pipe(2) -> Read(fd2[R]): %d, Write(fd2[W]): %d\n", (int) getpid(), fd2[R], fd2[W] );
    
    ret = fork();
    if (ret == 0) { //子プロセスへの命令
        printf ("[%d] CHILD\n", (int)getpid()); //デバッグ確認用
        
        close(fd1[W]);
        close(fd2[R]);
        
        /* 演算(エラトステネスの篩) */
        for(i=0; i<limit; i++)
            if(prime[i]) //(先頭から探索していった時に)素数フラグが立っていたら、
                for(j=2; (j*i)<limit; j++) prime[j*i]=0; //その倍数すべてに0フラグを立てる
        
        //素数配列を渡す
        write(fd2[W], prime, sizeof(int)*limit);
        printf("[%d] CHILD: WRITE TO fd[1].\n", (int)getpid()); //デバッグ確認用
        
    } else if (ret == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
        
    } else { //親プロセスへの命令
        printf ("[%d] PARENT\n", (int)getpid()); //デバッグ確認用
        
        close(fd1[R]);
        close(fd2[W]);
        
        
        //素数配列を受け取る
        read(fd2[R], prime, sizeof(int)*limit);
        printf("[%d] PARENT: READ FROM fd2[R].\n", (int)getpid()); //デバッグ確認用
        
        printf("\n");
        
        wait(&status);
        /* 素数出力 */
        for(i=0; i<limit; i++)
            if(prime[i]) { //素数だったら
                printf("%i ",i); //出力
                count++;
            }
        /* 素数の数出力 */
        printf("\n -> Process Done!! %d primes found!!", count);
    }
    
    return 0;
}



