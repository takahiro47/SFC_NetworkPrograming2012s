//
//  main.c
//  [20120416] Kaijo
//
//  Created by 土屋 貴裕 on 12/04/16.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>

#define MAX_VALUE 20

int main (int argc, const char * argv[]) {
    printf("\n");
    // insert code here...
    
    long i, j;
    j=1;
    for (i=1; i<MAX_VALUE; i++) {
        j = j*i;
        
        //左辺出力(!形式)
        printf("!%2ld = %ld\n", i, j);
    }
    printf("\n");
    
    return 0;
}



