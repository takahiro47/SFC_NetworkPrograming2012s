//
//  main.c
//  [20120425] fork_exec_pipe
//
//  Created by 貴裕 土屋 on 12/04/28.
//  Copyright (c) 2012年 家族. All rights reserved.
//

/* Part.03 - シェルsortのソートを動かしてみる
 * systemを使うやり方からは比較的容易に書き換えが出来る
 * 中間ファイルを生成しないので最後の削除作業は不要で、速度もこちらの方が少しだけ早い.
 * なお、popen()で得たファイルポインターはpclose()で閉じる。
 * 
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <signal.h>
#include <string.h>
//#include <errno.h>
//#include <sysproto.h>

#define R (0)
#define W (1)

int popen2(char *command, int *fd_r, int *fd_w);

int main(int argc, const char * argv[]) {
    char str[512];
    int fd_r, fd_w;
    int pid;
    char *outs = "ccc\naaa\nbbb\n";
    
    if((pid=popen2("sort", &fd_r, &fd_w)) == 0) {
        fprintf(stderr, "error!!!\n");
        exit(-1);
    }
    // sortに入力
    write(fd_w, outs, strlen(outs));
    close(fd_w);
    // sortから出力を受け取る。
    while(1) {
        if( read(fd_r, str, 1) == 0 ) {
            break;
        }
        str[1] = 0x00;
        printf("%s", str);
    }
    close(fd_r);
    return 0;
}

/*
 * char *command            :起動するプログラム名など
 * int *fd_r, int *fd_w     :ファイルディスクリプタを戻すためのポインタ変数
 */
int popen2(char *command, int *fd_r, int *fd_w) {
    int pipe_c2p[2], pipe_p2c[2];
    int pid;
    
    /* Create 2 of pipes */
    if ( pipe(pipe_c2p) < 0 ) {
        perror("popen2");
        return (-1);
    }
    if ( pipe(pipe_p2c) < 0 ) {
        perror("popen2");
        close(pipe_c2p[R]);
        close(pipe_c2p[W]);
        return (-1);
    }
    
    /* Invoke process */
    if ( (pid = fork()) < 0) {
        perror("popen2");
        close(pipe_c2p[R]);
        close(pipe_c2p[W]);
        close(pipe_p2c[R]);
        close(pipe_p2c[W]);
        return (-1);
    }
    if (pid == 0) { /* I'm child */
        close(pipe_p2c[W]);
        close(pipe_c2p[R]);
        dup2(pipe_p2c[R],0);
        dup2(pipe_c2p[W],1);
        close(pipe_p2c[R]);
        close(pipe_c2p[W]);
        if (execlp("sh","sh","-c",command,NULL) < 0) {
            perror("popen2");
            close(pipe_p2c[R]);
            close(pipe_c2p[W]);
            exit(1);
        }
    }
    
    close(pipe_p2c[R]);
    close(pipe_c2p[W]);
    *fd_w = pipe_p2c[W];
    *fd_r = pipe_c2p[W];
    
    return (pid);
}
