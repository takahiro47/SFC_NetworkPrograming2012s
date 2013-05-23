//
//  main.c
//  [20120416] command
//
//  Created by 土屋 貴裕 on 12/04/16.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, const char * argv[]) {
    // insert code here...
    
    if (argc != 4) {
        fprintf(stderr, "ERROR. 引数が足りません。\n---How to use:---\n$ ./a.out add <num1> <num2>\n  OR\n$ ./a.out sub <num1> <num2>");
        exit(EXIT_FAILURE);
    }
    
    int i;
    for (i=0; i<argc; i++) {
        if (!strcmp(argv[i], "add")) {
            printf("%d + %d = %d\n", atoi(argv[i+1]), atoi(argv[i+2]), (atoi(argv[i+1])+atoi(argv[i+2])) );
        } else if (!strcmp(argv[i], "sub")) {
            printf("%d - %d = %d\n", atoi(argv[i+1]), atoi(argv[i+2]), (atoi(argv[i+1])-atoi(argv[i+2])) );
        }
    }
    
    printf("\n");
    return 0;
}

