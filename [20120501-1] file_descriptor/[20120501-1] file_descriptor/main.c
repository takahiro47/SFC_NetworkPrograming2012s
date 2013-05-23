//
//  main.c
//  [20120501-1] file_descriptor
//
//  Created by 貴裕 土屋 on 12/05/01.
//  Copyright (c) 2012年 家族. All rights reserved.
//

/*
 * cat /etc/servicesの内容を解析
 * ftp	(space tab)     21/udp	(space tabs)	#comments
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/* prototypes */

/* variables */
void parse(char *buf, int cc);
void parseline(char *line);

/* main */
#pragma main
int main(int argc, const char * argv[]) {
    char buf[512];
    int fp, cc; //ファイル入出力系
    
    
    //How to use(引数で指定)
    /*
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    */
    
    //場所調べ、引数指定(デバッグ用に引数argv[1]を強制指定)
    argv[1] = "/etc/services";
    argc = 2;
    system("pwd");
    
    //file open
    if ((fp = open(argv[1], O_RDONLY)) < 0) { //O_RDONLY="r"
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    //file read
    while ((cc = (int)read(fp, buf, sizeof(buf))) > 0) {
        /* ファイルの中身を出力
        write(1, buf, cc); //ファイルディスクリプタの1番は標準出力
        fflush(stdout); */
        
        /* バッファを解析する関数を呼び出し */
        parse(buf, cc);
    }
    close(fp);
    
    return 0;
}


void parse(char *buf, int cc) {
    char *tp, *ep, *emdp;
    char line[512];
    
    emdp = buf + cc; //bufのアドレスよりもcc分のアドレスを移動するまで
    tp = buf;
    
    while ( tp < emdp ) {
        for (ep=tp; (*ep!='\n')&&(ep<emdp); ep++);
        
        *ep = '\0';
        strcpy(line, tp);
        
        printf("%s\n", line);
        parseline(line); //lineをそのまま出力ではつまらないので
        
        tp = ++ep;
    }
}


void parseline(char *line) {
    char *temp;
    int width;
    
    //行の長さを読み、出力(デバッグ用)
    width = strlen(line);
    printf("%d\n", width);
    
    
    temp = line;
    while ( temp < temp + width ) {
        printf("%s\n", line);
    }
    
}