//
//  main.c
//  [20120425] sosu_fork
//  ネットワークプログラミング 第2回
//  マルチプロセスで素数を算出するテスト
//  (アルゴリズムはただの条件付き総当たり)
//
//  Created by 貴裕 土屋 on 12/04/26.
//  Copyright (c) 2012年 家族. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h> //system()
#include <math.h>
//#include <string.h>
//#include <pthread.h>
//#include <sys/types.h>
//#include <sys/wait.h>

/* macros */
#define SEARCH_MAX 100000

/* prototypes */

/* variables */

/* main */
#pragma main
int main(int argc, const char * argv[]) {
    //prime : 1 = yes/素数である, 0 = no/素数ではない
    //limit : 素数
    unsigned long prime, limit;
    unsigned long i = 0, j = 3;
    
    printf("2 ");
    
    for (i = 3; i <= SEARCH_MAX; i += 2) {
        limit = ( (unsigned int)sqrt((double)i) ) + 1;
        prime = 1;
        j = 3; //jは判定対象の正の整数(3,5,7,,,)
        
        while (prime && (j <= limit)) {
            if (i%j == 0) { //3以上の奇数で割り切れたら
                prime = 0;
            }
            j += 2;
        }
        
        if (prime) { //素数だったら
            printf("%ld ", i);
//            if (i%4 == 1) { numP41++; } //4k + 1 primes
//            if (i%4 == 3) { numP43++; } //4k - 1 primes
        }
    }
    
    printf("Process Done! \n");
    return 0;
}

/* ------------------------------------------------
 unsigned int *alloc_prime_tab(unsigned int n)
 メモリ領域を確保する関数
 input  >> unsigned int n: 素数をサーチする数字の上限
 return >> unsigned int ip: 確保したメモリ番地？
 ------------------------------------------------- */ /*
unsigned int prime_maker() {
    if () {
        
    }
}
*/