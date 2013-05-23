//
//  main.c
//  [20120709] Twitter4C
//
//  Created by 貴裕 土屋 on 12/07/09.
//  Copyright (c) 2012年 家族. All rights reserved.
//

/**
 * =課題・問題点=
 *　ツイッターに投稿するC言語のAPIが1つしか見つからず、
 * しかしそれが仕様が古いものだったため、それを対応する
 * ようにがんばっていたら、対応させるどことか、肝心のネ
 * ットワークプログラミングに費やす時間がなくなってしま
 * いました。
 * -------------------------------------- */


/*
 * Port番号(サービス名): ****
 * Usage: ./main [status]
 */


#include <stdio.h>
#include <stdlib.h>     // exit()
#include <string.h>     // bzero()
#include <sys/types.h>
#include <sys/socket.h> // socket(), bind(), listen(), accept(), recv()
#include <netinet/in.h> // htons()
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include "twilib.h"

#define PORT    5356    // Listenするポート
#define BUF_SIZE 1024    // 受信バッファサイズ

//
static char const consumer_key[] = "RXHEC2y3d5O28MErNk2zbA";
static char const consumer_secret[] = "bxo82aQzqPlRXtn7c7hTtMMYfCbH585iIUZJyrEyU";

void RemoveReturn(char *str, int size) {
    int i=0;
    while(str[i] != 0 && i != size) {
        if(str[i] == '\r' || str[i] == '\n') str[i] = 0;
        i++;
    }
}

int main2(int argc, const char * argv[]) {
    /**
     * =変数
     * -------------------------------------- */
    /* ソケット接続用変数群 */
    struct addrinfo hints;
    struct addinfo *result, *rp;
    struct sockaddr_in saddr; // サーバ用アドレス格納構造体
    struct sockaddr_in caddr; // クライアント用アドレス格納構造体
    
    int listen_fd;
    int conn_fd;
    
    int len = sizeof(struct sockaddr_in);
    
    int rsize; //受信バッファサイズ保管用
    char buf[BUF_SIZE]; //受信バッファ
    
    
    /* ツイート用変数群 */
    int errcode = 0;
    char pin[20] = {0};
    char *errcode_c = 0;
    FILE *access_token;
    
    
    /**
     * =以下コード
     * -------------------------------------- */
    
    
    // ソケット生成
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    // saddrの中身を0に
    bzero((char *)&saddr, sizeof(saddr));
    
    // ソケットにアドレスとポート
    saddr.sin_family        = PF_INET;
    saddr.sin_addr.s_addr   = INADDR_ANY;
    saddr.sin_port          = htons(PORT);
    if (bind(listen_fd, (struct sockaddr *)&saddr, len) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    // ポートListen
    if (listen(listen_fd, SOMAXCONN) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Start Listen Port (%d)\n", PORT);
    
    // 接続要求を受付け
    if ((conn_fd = accept(listen_fd, (struct sockaddr *)&caddr, &len)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    // Listenソケットクローズ
    close(listen_fd);
    
    // 送信されたデータの読み出し
    char* p = malloc(36);
    strcat(p, "Usage: [text(you want to tweet)]\n");
    
    do {
        rsize = recv(conn_fd, buf, BUF_SIZE, 0);
        
        if (rsize == 0) { // クラアイント切断時
            break;
        } else if (rsize == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        } else {
            /*
            char* p = malloc(strlen(buf) + 256);
            strcpy(p, buf);
            strcat(p, "Usage: [text(you want to tweet)]\n");
            */
            write(conn_fd, p, rsize + 10);
        }
    } while (1);
    
    if ( close(conn_fd) < 0) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    
    printf("Connection closed.\n");
    
    
    exit(EXIT_SUCCESS);
}


/*
 * 以下、ツイートするための関数(未完成)
 */
int main(int argc, const char * argv[]) {
    int errcode = 0;
    char pin[20] = {0};
    char *errcode_c = 0;
    FILE *access_token;
    
    char usr[20] = {0}, id[20] = {0}, token[150] = {0}, secret[150] = {0};
    
    if (argc != 2) {
        printf("Usage: ./main.out [Usage: [text(you want to tweet)]]\n");
        exit(0);
    }
    
    struct Twitter_consumer_token *c;
    struct Twitter_request_token *r;
    struct Twitter_access_token *a;
    
    c = (struct Twitter_consumer_token *) calloc(1, sizeof(struct Twitter_consumer_token));
    r = (struct Twitter_request_token *) calloc(1, sizeof(struct Twitter_request_token));
    a = (struct Twitter_access_token *) calloc(1, sizeof(struct Twitter_access_token));
    
    //取得したコンシューマキーとコンシューマシークレットをセットする
    char consumer_key[] = "RXHEC2y3d5O28MErNk2zbA";
    char consumer_secret[] = "bxo82aQzqPlRXtn7c7hTtMMYfCbH585iIUZJyrEyU";
    
    c->consumer_key = consumer_key;
    c->consumer_secret = consumer_secret;
    
    //アクセストークンを保存する
    access_token = fopen("access_token.txt", "r");
    
    if (access_token == NULL) {
        //リクエストトークン取得
        printf("start to get request token\n");
        
        printf("now connecting...");
        if(errcode = Twitter_GetRequestToken(c, r), errcode < 0) {
            printf("\nError in get request token\n");
            if(errcode < -8) printf("Error Code:%d (Connection error)\n", errcode);
            else  printf("エラーコード:%d（内部処理エラー）\n", errcode);
            exit(0);
        }
        
        printf("OK.\n%s%s ここにアクセスしてPINコードを取得してください。\nPIN:", "https://api.twitter.com/oauth/authorize?oauth_token=", r->request_token);
        if(scanf("%19s%*[^\n]", pin) == -1) {
            printf("入力エラーです。\n");
            exit(EXIT_FAILURE);
        }
        a->pin = pin;
        
        printf("アクセストークンを取得しています...");
        if(errcode = Twitter_GetAccessToken(c, r, a), errcode < 0) {
            printf("\nアクセストークンの取得でエラーが発生しました。\n");
            if(errcode < -8) printf("エラーコード:%d（通信エラー）\n", errcode);
            else  printf("エラーコード:%d（内部処理エラー）\n", errcode);
            exit(0);
        }
        
        access_token = fopen("access_token.txt", "w");
        if(access_token == NULL) {
            printf("Error\n");
            exit(0);
        }
        fprintf(access_token, "%s\n%s\n%s\n%s\n%s\n", a->screen_name, a->user_id, a->access_token, a->access_secret, a->pin);
        fclose(access_token);
    }
    
    else {
        //ファイルから必要な情報を取り出す
        if(errcode_c = fgets(usr, 20, access_token), errcode_c == NULL) return -1;
        if(errcode_c = fgets(id, 20, access_token), errcode_c == NULL) return -1;
        if(errcode_c = fgets(token, 150, access_token), errcode_c == NULL) return -1;
        if(errcode_c = fgets(secret, 150, access_token), errcode_c == NULL) return -1;
        if(errcode_c = fgets(pin, 20, access_token), errcode_c == NULL) return -1;
        
        RemoveReturn(usr, 20);
        RemoveReturn(id, 20);
        RemoveReturn(token, 150);
        RemoveReturn(secret, 150);
        RemoveReturn(pin, 20);
        
        a->user_id = usr;
        a->access_token = token;
        a->access_secret = secret;
        a->pin = pin;
        fclose(access_token);
    }
    
    printf("OK.\nようこそ %s(ID:%s) さん。\n", a->screen_name, a->user_id);
    
    printf("ツイートしています...");
    if(errcode = Twitter_UpdateStatus(c, a, argv[1]), errcode < 0) {
        printf("\nツイートでエラーが発生しています\n");
        if(errcode < -8) printf("エラーコード:%d（通信エラー）\n", errcode);
        else  printf("エラーコード:%d（内部処理エラー）\n", errcode);
        exit(0);
    }
    else printf("OK.\nツイートに成功しました。\n");
    
    return 0;
}
