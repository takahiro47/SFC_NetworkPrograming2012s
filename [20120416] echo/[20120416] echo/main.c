//
//  main.c
//  [20120416] echo
//
//  Created by 土屋 貴裕 on 12/04/16.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>

int main (int argc, const char * argv[]) {
    // insert code here...
    
    if (argc <= 2) {
        printf("\n引数がありません。最低1つ以上を入力してください。\n");
        return 0;
    } else {
        printf("\n");
        for (int i=1; i<=argc; i++) {
            printf("%s ", argv[i-1]);
        }
        printf("\n");
    }
    return 0;
}

