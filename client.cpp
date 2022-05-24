#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(){
    struct sockaddr_in serv_addr;
    int opt = 1;
    int valread = 0;
    char buffer[1024] = {0};
    char * hello = "hello";
    int sockfdd2 =socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    connect(sockfdd2, (sockaddr*)&serv_addr,  sizeof(serv_addr));
     send(sockfdd2, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sockfdd2, buffer, 1024);
    printf("%s\n", buffer);
    while (1);
    return 0;
   // setsockopt(sockfdd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt));

}