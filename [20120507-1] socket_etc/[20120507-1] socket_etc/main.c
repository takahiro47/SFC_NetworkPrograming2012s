//
//  main.c
//  [20120507-1] socket_etc
//
//  Created by 貴裕 土屋 on 12/05/07.
//  Copyright (c) 2012年 家族. All rights reserved.
//


/*
 * Host名: "nepro.sfc.wide.ad.jp"
 * Port番号(サービス名): 12345
 */


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SIZE 500

int main(int argc, const char * argv[]) {
    struct addrinfo hints;
    struct addinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];
    
    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* Obtain address(es) matching host/port */
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */
    
    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    /* getaddrinfo() returns a list of address structures.
     Try each address until we successfully connect(2).
     If socket(2) (or connect(2)) fails, we (close the socket
     and) try the next address. */
    
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;
        
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */
        
        close(sfd);
    }
    
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }
    
    freeaddrinfo(result);           /* No longer needed */
    
    /* Send remaining command-line arguments as separate
     datagrams, and read responses from server */
    
    for (j = 3; j < argc; j++) {
        len = strlen(argv[j]) + 1;
        /* +1 for terminating null byte */
        
        if (len + 1 > BUF_SIZE) {
            fprintf(stderr, "Ignoring long message in argument %d\n", j);
            continue;
        }
        
        if (write(sfd, argv[j], len) != len) {
            fprintf(stderr, "partial/failed write\n");
            exit(EXIT_FAILURE);
        }
        
        nread = read(sfd, buf, BUF_SIZE);
        if (nread == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        printf("Received %ld bytes: %s\n", (long) nread, buf);
    }
    
    exit(EXIT_SUCCESS);
}
    
    /*
    strcpy(host, "nepro.sfc.wide.ad.jp");
    port = 12345;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    error = getaddrinfo(host, port, &hints, &res0); //IPアドレスのリストの頭へのポインタを取得
    
    
    if (error) {
        errx(1, "%s", gai_strerror(error));
        * NOTREACHED *
    }
    s = -1;
    for (res=res0; res; res=res->ai_next) {
        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        
        if (socket < 0) {
            cause = "socket";
            continue;
        }
        if (connect(socket, res->ai_addr, res->ai_addrlen) < 0) {
            cause = "connect";
            close(socket);
            socket = -1;
            continue;
        }
        break;
    }
    
    if (socket < 0) {
        err(1, "%s", cause);
    }
    
    freeaddreinfo(res0);
    
    return 0;
}
     */

