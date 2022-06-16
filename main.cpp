
   
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include "Request.hpp"
#include <stdlib.h>
#include <sys/select.h>
#define PORT 9090

int  findfirstline(std::string data)
{
	std::string stringg[9];
	stringg[0] ="GET";
	stringg[1] ="POST";
	stringg[2] ="DELETE";

	std::string tmp;
	tmp = data.substr(0,data.find(" "));
	std::cout<<tmp<<std::endl;

	for (int i = 0; i <= 2 ; i++)
	{
			if (tmp.find(stringg[i]) == 0)
			{
				return i;
			}
	}
	tmp.erase();
	std::cout<<"im hererererere"<<std::endl;
	return(-1);
}


int main(){
	char *buffer = (char *)malloc(sizeof(char) * 1024 + 1);
	int activ;
	int clientsocket[30];
	Request req;
	int max_sd;
	int sd;
	char *hello =  "HTTP/1.1 200 OK\r\nAccept-Ranges: bytes\r\nContent-Length: 45\r\nContent-Type: text/plain\r\n\r\nHello World! My payload includes a trailing CRLF."; 
	int opt = 1;

	for (int i = 0;i < 30; i++)
		clientsocket[i] = 0;
	int new_socket;
	
	fd_set readsfds;
	int valread = 0;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int sockfd = socket(PF_INET,SOCK_STREAM,0); 
	req.set_socketid(new_socket);
	setsockopt(sockfd ,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(PORT);
	bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	listen(sockfd, 3);
	while (true)
	{
		FD_ZERO(&readsfds);
		FD_SET(sockfd, &readsfds);
		max_sd =  sockfd;
		for(int i = 0;i < 30;i++)
		{
			sd = clientsocket[i];
			if (sd > 0)
				FD_SET(sd, &readsfds);
			if (sd > max_sd )
				max_sd = sd;
		}
		int c = 0;
		int count = 0;
		activ = select(max_sd + 1, &readsfds, NULL, NULL, NULL);
		if (FD_ISSET(sockfd, &readsfds))
		{
			new_socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
			req.set_socketid(new_socket);
			valread = read(new_socket, buffer, 1024);
			buffer[valread] = '\0';
			req.parserequest(buffer, 1024);
			//std::cout<<"im hereeeeeeeeeee"<<std::endl;
			printf("Hello message sent\n");
				for(int i = 0 ;i < 30;i++)
				{
					if (clientsocket[i] == 0)
					{
						clientsocket[i] = new_socket;
						break;
					}
				}
		}
			      //else its some IO operation on some other socket
        for (int i = 0; i < 30; i++)  
        {  
            sd = clientsocket[i];  
                 
            if (FD_ISSET( sd , &readsfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    clientsocket[i] = 0;  
                }  
                else 
                {  
                    buffer[valread] = '\0';  
                    send(sd , buffer , strlen(buffer) , 0 );  
                }  
            }  
        } 
		}
		


		while (1);
		return 0;
	}