//
//  main.c
//  [20120425] system
//
//  Created by 貴裕 土屋 on 12/04/27.
//  Copyright (c) 2012年 家族. All rights reserved.
//

/* Part.01
 * system("ls -1")だとただ単純に出力されてので一度中間ファイルにリダイレクトし、
 * その後それを読み込むことで実現している。
 * ※ただしこのように中間ファイル(tmpファイル)を使うことはあまり好ましくない
 * 参考URI: http://www.ncad.co.jp/~komata/c-kouza3.htm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

int main(int argc, const char * argv[]) {
    char filename[80], str[512], *ptr;
    FILE *fp;
    
    //lsコマンドを実行し、中間ファイルを生成
    sprintf(filename, "/tmp/ls%d.tmp", getpid()); //フォルダ名にtmpとプロセスIDをつけて重複を防止
    sprintf(str, "ls -1 > %s", filename); //-1で1行に1つのエントリ
    system(str);
    
    //読み取りエラー判定
    if ((fp=fopen(filename,"r")) == NULL) {
        fprintf(stderr, "error!!!\n"); exit(-1);
    }

    //
    while (1) {
        fgets(str, 512, fp); //ファイルから1行読み込み
        if (feof(fp)) { //ファイルの末端に到達したらループを終了する
            break;
        }
        ptr = strchr(str, '\n'); //strchrで\nの位置を探し、最初に見つかった位置をポインタで返す
        if (ptr != NULL) { //見つかったら
            *ptr = '\0';
        }
        printf("%s\n", str);
    }
    fclose(fp);
    
    //中間ファイルを削除
    sprintf(str, "rm -f %s", filename); //-fは強制削除指示。これが無いと削除確認のダイアログ等が出てしまう可能性がある
    system(str);
    
    return 0;
}