#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8181

int main(){

    int s,c;
    socklen_t addrlen;
    addrlen=0;
    char buff[512];
    char *data;

    struct sockaddr_in srv, cli;

    memset(&srv,0,sizeof(srv));
    memset(&cli,0,sizeof(cli));

    s=socket(AF_INET,SOCK_STREAM,0);
    if (s < 0){
        printf("socket() \n");
        return -1;
    }

    srv.sin_family=AF_INET;
    srv.sin_addr.s_addr=0;
    srv.sin_port=htons(PORT);

    if(bind(s,(struct sockaddr *)&srv,sizeof(srv)) < 0){
        printf("bind() \n");
        close(s);
        return -1;
    }
    
    if (listen(s,5) < 0){
        printf("listen() \n");
        close(s);
        return -1;
    } //5 -> five user can connect to our server simultaneously.

    printf("Listening on 0.0.0.0:%d",PORT);
    c=accept(s, (struct sockaddr *)&srv,&addrlen);
    if (c <0 ){
        printf("accept() \n");
        close(s);
        return -1;
    }

    printf("Client connected \n");
    read(c,buff,511);

    data="httpd v1.1\n";
    write(c,data,strlen(data));
    close(c);
    close(s);

    return 0;
}
