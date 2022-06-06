
   
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include "Request.hpp"
#include <sys/select.h>
#define PORT 7070

int  findfirstline(std::string *tab)
{
	std::string stringg[9];
	stringg[0] ="GET ";
	stringg[1] ="POST ";
	stringg[2] ="DELETE ";
	

	for (int i = 0; i <= 2 ; i++)
	{
		if (tab[0].find(stringg[i]) == 0)
		{
			return i;
		}
	}
	return(-1);
}


int main(){
	char buffer[1024] = { 0 };
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
	std::string headersfield[5] = {"Host","Connection","Content-Length","Content-Type","Transfer-Encoding"};
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


			while (buffer[c] != '\0')
			{
				if (buffer[c] == '\n')
					count++;
				c++;
			}
			std::cout<<count<<"count";
			std::string tab[count + 1];
			int j =0 ;
			c = 0;
			while (buffer[c] != '\0')
			{
				if (buffer[c] == '\n')
				{
					j++;
					c++;
				}
				if (buffer[c] != '\r')
					tab[j] += buffer[c];
				c++;
			}
			for (int i = 0; i < count + 1; i++)
				std::cout<<"LINE = "<< i << " " <<tab[i]<<std::endl;
			int count2 = 0;
			if (findfirstline(tab) != -1)
			{
				for(int i = 0; i < tab[0].size(); i++)
				{
					if (tab[0][i] != ' ')
					{
						count2++;
						std::string op;
						while(tab[0][i] != ' ' && i < tab[0].size())
						{
							op += tab[0][i];
							i++;
						}
						if (count2 == 1)
							req.setmethod(op);
						else if (count2 == 2)
							req.setrequest(op);
						else
							req.sethttpversion(op.substr(0,op.size()));
						op.erase();
					}
				}
				std::cout<<"first line :"<<tab[0]<<std::endl;
				int p;
				for (int i = 1; i < count; i++)
				{
					p = tab[i].find(":");
					for(int j = 0; j < p; j++)
					{
						if (tab[i][j] == ' ')
							return 0;
					}
					std::string sub;
					sub = tab[i].substr(0, p);
					if (sub.compare(headersfield[0])== 0)
						req.sethost(tab[i].substr(p + 2));
					if (sub.compare(headersfield[1])== 0)
						req.setconnection(tab[i].substr(p + 2));
					if (sub.compare(headersfield[2])== 0)
						req.setcontent_length(tab[i].substr(p + 2));
					if (sub.compare(headersfield[3])== 0)
						req.setcontent_type(tab[i].substr(p + 2));
					if (sub.compare(headersfield[4])== 0)
							req.settransferchunks(tab[i].substr(p + 2));
				}
				std::cout<<"couunt is " <<count2<<std::endl;
				}
				std::cout<<"method : "<<req.get_method()<<std::endl;
				std::cout<<"request ur : "<<req.get_requestur()<<std::endl;
				std::cout<<"http version: "<<"|"<<req.get_httpversion()<<"|"<<std::endl;  
				std::cout<<"Host : " <<req.gethost()<<std::endl;     
				std::cout<<"Connection : "<<req.get_connection()<<std::endl;  
				send(new_socket, hello, strlen(hello), 0);
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
		



		return 0;
	}