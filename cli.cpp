#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include "netdb.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "string.h"
#include "memory.h"
#include "signal.h"
#include "time.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int socket_connect(int port,char *host){
    int sockfd;
    struct sockaddr_in dest_addr;
    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket error");
        return 1;
    }

    memset(&dest_addr,0,sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);

    fflush(stdout);
    if (connect(sockfd,(struct sockaddr *)&dest_addr,sizeof(dest_addr)) < 0){
        return -1;
    }
    return sockfd;
}

int main(){
    int port = 8778;
    char host[50] = "192.168.1.141";
    FILE * fin = fopen("in","r");
    char mes[50];
    int sockfd = socket_connect(port,host);
    while (~fscanf(fin,"%s",mes)){
       printf("we recceive : %s \n",mes);
       send(sockfd,mes,strlen(mes),0);
    }
    return 0;
}