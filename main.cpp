
 #include "Webserver.hpp"  
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
#include <fcntl.h>
#include <map>
#define PORT 7799
#define BUFFERSIZE 2048


int readpo = 0;
int  findfirstline(std::string data)
{
	std::string stringg[9];
	stringg[0] ="GET";
	stringg[1] ="POST";
	stringg[2] ="DELETE";

	std::string tmp;
	tmp = data.substr(0,data.find(" "));
	////std::cout<<tmp<<std::endl;

	for (int i = 0; i <= 2 ; i++)
	{
			if (tmp.find(stringg[i]) == 0)
			{
				return i;
			}
	}
	tmp.erase();
	return(-1);
}


int main(int argc, char **argv){
	// if (!argv[1])
	// {
	// 	std::cout << argc<< std::endl;
	// 	return (1);
	// }
	argc = 1;
	// else
	// {
		signal(SIGPIPE,SIG_IGN);
		std::string lop;
		lop.append(argv[1]);
		Webserver op(lop);
		op.webservbuild();
		op.Runmywebserver();
	// }
	// return (0);
	//signal(SIGPIPE, SIG_IGN);
	//char *buffer = (char *)malloc(sizeof(char) * BUFFERSIZE + 1);
	//int activ;
	//int wahedl9laoui;
	//int clientsocket[30];
	//Request req;
	//std::map<int, Request> Requestsmap;
	////std::vector<Request> op;
	//int max_sd;
	//int sd;
	////char *hello =  "HTTP/1.1 200 OK\r\nAccept-Ranges: bytes\r\nContent-Length: 45\r\nContent-Type: text/plain\r\n\r\nHello World! My payload includes a trailing CRLF."; 
	//int opt = 1;
//
	//for (int i = 0;i < 30; i++)
	//	clientsocket[i] = 0;
	//int new_socket;
	//
	//fd_set readsfds;
	//int valread = 0;
	//struct sockaddr_in address;
	//int addrlen = sizeof(address);
	//int sockfd = socket(PF_INET,SOCK_STREAM,0); 
	//req.set_socketid(new_socket);
	//setsockopt(sockfd ,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	//address.sin_family = AF_INET;
	//address.sin_addr.s_addr = inet_addr("127.0.0.1");
	//address.sin_port = htons(PORT);
	//bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	//listen(sockfd, 3);
	//while (true)
	//{
	////	//std::cout << "DBG__MAIN__LOOP" << std::endl;
	//	FD_ZERO(&readsfds);
	//	FD_SET(sockfd, &readsfds);
	//	max_sd =  sockfd;
	//	for(int i = 0;i < 30;i++)
	//	{
	//		sd = clientsocket[i];
	//		if (sd > 0)
	//			FD_SET(sd, &readsfds);
	//		if (sd > max_sd )
	//			max_sd = sd;
	//	}
	//	int c = 0;
	//	int count = 0;
	//	activ = select(max_sd + 1, &readsfds, NULL, NULL, NULL);
	//	if (FD_ISSET(sockfd, &readsfds))
	//	{
	//		new_socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	//		req.set_socketid(new_socket);
	//		
	//		readpo +=(valread = read(new_socket, buffer,BUFFERSIZE));
	//		buffer[valread] = '\0';
	//		std::string str;
	//		str.append(buffer);
	//	//	//std::cout<<str;
	//		if (req.get_requestiscomplete() == true)
	//							break;
	//		req.parserequest(buffer, valread);
	//		////std::cout<<"im hereeeeeeeeeee"<<std::endl;
	//		Requestsmap[new_socket] = req;
	//		//printf("Hello message sent\n");
	//			for(int i = 0 ;i < 30;i++)
	//			{
	//				if (clientsocket[i] == 0)
	//				{
	//					clientsocket[i] = new_socket;
	//					break;
	//				}
	//			}
	//	}
	//		      //else its some IO operation on some other socket
	//	
	//    for (int i = 0; i < 30; i++)  
    //    {  
	//		////std::cout << "DBG__FOR__LOOP" << std::endl;
    //        
	//		sd = clientsocket[i];  
	//			////std::cout<<"allo"<<std::endl;
    //        if (FD_ISSET( sd , &readsfds))  
    //        {  
	//			////std::cout << "CONDITION__00" << std::endl;
	//			std::map<int, Request>::iterator it;
    //            //Check if it was for closing , and also read the 
    //            //incoming message 
	//			wahedl9laoui = open("test.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
    //            // if ((valread = read( sd , buffer, BUFFERSIZE)) == 0)  
    //            valread = read( sd , buffer, BUFFERSIZE);
	//			buffer[valread] = '\0';
    //            //std::cout << "RET_READ : " << valread << std::endl;
	//			if (valread < 10)
	//				//std::cout << "EXCEPTION : [" << buffer << "]" << std::endl;
	//			readpo += valread;
	//			 //std::cout << "ALL SIZR: " << readpo<< std::endl;
	//			if (valread == 0)  
    //            {  
	//				
	//				
    //                //Somebody disconnected , get his details and print 
    //                getpeername(sd , (struct sockaddr*)&address , \
    //                    (socklen_t*)&addrlen);  
    //                printf("Host disconnected , ip %s , port %d \n" , 
    //                      inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
    //                     
    //                //Close the socket and mark as 0 in list for reuse 
    //                close( sd );  
	//				
    //                clientsocket[i] = 0;  
    //            }  
    //            else 
    //            {  
	//			////std::cout << "CONDITION__01" << std::endl;
	//				std::string str2;
	//		////std::cout<<str2.append(buffer)<<std::endl;
	//			//	write(wahedl9laoui,buffer,valread);
    //                buffer[valread] = '\0';  
	//				for (std::map<int, Request>::iterator it = Requestsmap.begin(); it != Requestsmap.end(); ++it)
	//				{
	//					if (it->first == sd)
	//					{
	//					//	if (it->second.)
	//						if (it->second.get_requestiscomplete() == true)
	//							break;
	//					//	it->second.adddata(buffer, valread);
	//					//	//std::cout<<" i m heree ------------ "<< sd<<std::endl;
	//						it->second.parserequest(buffer, valread);
	//					}
	//				}
	//				str2.erase();
    //                //send(sd , buffer , strlen(buffer) , 0 );
	//		  
    //            }
	//			////std::cout << "CONDITION__02" << std::endl;
	//			close(wahedl9laoui);
    //        }  
    //    } 
	//}
	}
