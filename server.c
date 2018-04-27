#include "common.h"

int scoket_create(int port,char *ip){


   int sockfd ;
   //1.socket 
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if (sockfd < 0){
      printf("socket error!\n");
   }else {
      printf("socket OK!\n");
   }
   //2.connect
   struct sockaddr_in addr_in;
   memset(&addr_in,0,sizeof(addr_in));
   addr_in.sin_family = AF_INET;
   addr_in.sin_port = htons(port);
   addr_in.sin_addr.s_addr = inet_addr(ip);
   
   if (connect(sockfd,(struct sockaddr *)&addr_in,sizeof(addr_in)) < 0){
       printf("connect error\n");
   }else {
       printf("connect OK!\n");
   }
   DBUG("port :%d  IP: %s\n",port,ip);
   return sockfd;

}

int main(int argc, char** argv)
{
   char ip[80] = "192.141.1.141";
   int soc = scoket_create(1235,ip);
   struct sockaddr_in peer;
   socklen_t peer_len = sizeof(struct sockaddr_in);
   bzero(&peer, sizeof(struct sockaddr_in));
   getpeername(soc, (struct sockaddr *)&peer, &peer_len);
   char buff_peer[64] = {'\0'};
   DBUG("CLIENT : %s \n",inet_ntop(AF_INET, (void*)&peer.sin_addr, buff_peer, 63));
   return 0;
}