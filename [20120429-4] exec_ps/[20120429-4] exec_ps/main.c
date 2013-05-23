//
//  main.c
//  [20120429-4] exec_ps
//
//  Created by 貴裕 土屋 on 12/04/29.
//  Copyright (c) 2012年 家族. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    printf("Exec ps program...\n");
    execlp("ls","ls","-al",NULL);
    printf("done.\n");
    
    return 0;
}

