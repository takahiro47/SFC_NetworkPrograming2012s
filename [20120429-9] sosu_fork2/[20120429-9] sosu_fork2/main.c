//
//  main.c
//  [20120429-9] sosu_fork2
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

/*
 * fork()などの関数を追加する前の所まで
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    char tmp[100];
    int limit ,i, j, count = 0, *prime;
    
    /* 上限を指定 */
    printf("探索する上限の数： ");
    fgets(tmp, 100, stdin);
    limit = atoi(tmp) + 1; //上限の数(自身も含める)
    
    /* メモリ確保と初期化 */
    prime = (int*)malloc(sizeof(int)*limit);
    prime[0] = prime[1] = 0; //0,1は素数でない
    for(i=2; i<limit; i++) prime[i]=1; //全ての数に1を立てて初期化(1は素数, 0は合成数)
    
    /* エラトステネスの篩 */
    for(i=0; i<limit; i++)
        if(prime[i]) //(先頭から探索していった時に)素数フラグが立っていたら、
            for(j=2; (j*i)<limit; j++) prime[j*i]=0; //その倍数すべてに0フラグを立てる
    
    /* 素数出力 */
    for(i=0; i<limit; i++)
        if(prime[i]) { //素数だったら
            printf("%i ",i); //出力
            count++;
        }
    
    /* 素数の数出力 */
    printf("\n -> Process Done!! %d primes found!!", count);
    
    return 0;
}