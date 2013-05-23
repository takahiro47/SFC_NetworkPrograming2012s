//
//  main.c
//  [20120424] popen
//
//  Created by 貴裕 土屋 on 12/04/27.
//  Copyright (c) 2012年 家族. All rights reserved.
//

/* Part.02
 * systemを使うやり方からは比較的容易に書き換えが出来る
 * 中間ファイルを生成しないので最後の削除作業は不要で、速度もこちらの方が少しだけ早い.
 * なお、popen()で得たファイルポインターはpclose()で閉じる。
 * ※ただしこのように中間ファイル(tmpファイル)を使うことはあまり好ましくない
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char str[512], *ptr;
    FILE *fp;
    
    if ((fp=popen("ls -1", "r")) == NULL) { //自分のプログラムとlsの間にパイプを設け、"r"=読み込みをしている
        fprintf(stderr,"error!!!\n"); exit(-1);
    }
    
    while (1) {
        fgets(str,512,fp);
        if (feof(fp)) {
            break;
        }
        ptr = strchr(str,'\n');
        if (ptr != NULL) {
            *ptr = '\0';
        }
        
        printf("%s\n", str);
    }
    pclose(fp);
    
    return 0;
}