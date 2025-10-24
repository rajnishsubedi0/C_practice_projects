#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define IP "142.251.43.99" //Ip of google.com, to get this just do `host www.google.com` or ping google.
#define PORT 80 

int main(){
   int s;
  struct sockaddr_in sock; //exat name sockaddr_in is compulsory.
   char buf[512];// 512 size of buffer is perfect for test. Long buffer size will capture long datas from socket. 512 buffer size just holds OK http response and little information about response.
   char *data;
   data="HEAD / HTTP/1.0\n\n"; //Sockets tries to connect using this header and response will be printed on below printf("").

   s=socket(AF_INET, SOCK_STREAM,0);

   if (s<0){
      printf("socket() error\n");//we also can eliminate socket(). It is just to display error.
      return -1;
   }
   
   sock.sin_addr.s_addr= inet_addr(IP);
   sock.sin_port=htons(PORT);
   sock.sin_family=AF_INET;
   if(connect(s,(struct sockaddr *)&sock,sizeof(struct sockaddr_in)) !=0){
         printf("connect() error \n");
         close(s);
         return -1;
   }

   write (s,data,strlen(data) );
   read(s,buf,511);
   close(s);
   printf("%s\n",buf);
   return 0;
}
