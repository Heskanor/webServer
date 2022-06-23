#include "Webserver.hpp"
#define BUFFERSIZE 15000
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Webserver::Webserver(std::string _path)
{
	path = _path;
}

Webserver::Webserver( const Webserver & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Webserver::~Webserver()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Webserver &				Webserver::operator=( Webserver const & rhs )
{
	lopserver = rhs.lopserver;
	Requestsmap = rhs.Requestsmap;
	master = rhs.master;
	path = rhs.path;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Webserver const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/
bool 				Webserver::checkifisserver(int i)
{
	for(std::map<int,Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
	{
		if (it->second.fd == i)
			return true;
	}
	return(false);
}
bool				Webserver::checkifitsfdserver(int i)
{
	for(std::map<int,Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
	{
		if (it->second.fd == i)
			return true;
	}
	return false;
}
void				Webserver::Runmywebserver()
{
	fd_set readsfds;
	fd_set writefds;
	char *buffer = (char *)malloc(sizeof(char) * (BUFFERSIZE + 1));
	int valread = 0;
	FD_ZERO(&readsfds);
	FD_ZERO(&writefds);
	int new_socket ;
	Request req;
	int activ;
	int max_sd = -1;
	std::map<int,Myserver>::iterator it;
	for(std::map<int,Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
	{
		if (it->second.fd > max_sd)
			max_sd = it->second.fd;
	}
	while (true)
	{

	//	//std::cout << "DBG__MAIN__LOOP" << std::endl;
		 readsfds =  master ;
		//max_sd =  sockfd;

		activ = select(max_sd + 1, &readsfds, &writefds, NULL, NULL);
		for (int i =0; i < max_sd + 1; i++)
		{
			if (FD_ISSET(i, &readsfds) || FD_ISSET(i,&writefds))
			{
				if (checkifisserver(i) == true)
				{
					new_socket = accept(lopserver[i].fd, (struct sockaddr*)&lopserver[i].address, (socklen_t*)&lopserver[i].addrlen);
					req.set_socketid(new_socket);
					req.set_timeout(time_now());
					for(std::map<int,Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
					{
						std::cout<<"i really here"<<std::endl;
						if (it->second.fd == i)
						{
							req.setserver_fd(it->second.index);
							std::cout<<it->second.index<<"|||||||||||"<<std::endl;
						}
						//if (it->second.fd > max_sd)
						//max_sd = it->second.fd;
					}
					//req.setserver_fd(i);
					Requestsmap[new_socket] = req;
					FD_SET(new_socket,&master);
					if (new_socket > max_sd)
						max_sd = new_socket;
				}
				else
				{
					if (FD_ISSET(i, &readsfds))
					{
							 valread = read( i , buffer, BUFFERSIZE);
							 std::cout<<valread<<std::endl;
								buffer[valread] = '\0';
								if(valread == 0)
									{
										std::cout<<"sadsadasD"<<std::endl;
									}
					if(valread == 0  && ((time_now() - Requestsmap[i].get_timeout()) >5000))
					{
														std::cout<<" im here  6666 "<<std::endl;
//
						FD_CLR(i,&readsfds);
						  close(i); 
					}
					else
					{
					for (std::map<int, Request>::iterator it = Requestsmap.begin(); it != Requestsmap.end(); ++it)
					{
						if (it->first == i)
						{
						//	if (it->second.)
							it->second.parserequest(buffer, valread);
						Requestsmap[i].set_timeout(time_now());
							if (it->second.get_requestiscomplete() == true)
							{
								std::cout<<" im here "<<std::endl;
								Response resp;
								std::cout<<req.getserver_fd()<<std::endl;
								resp = server_response(it->second,servers[req.getserver_fd()]);
								Responsemap[it->first] = resp;
								FD_CLR(it->first,&readsfds);
								FD_SET(it->first, &writefds);

							}
						//	it->second.adddata(buffer, valread);
						//	//std::cout<<" i m heree ------------ "<< sd<<std::endl;
						//}
					}
						}
					//}
				}
				if (FD_ISSET(i, &writefds))
					{
						std::string lop;
						lop = Responsemap[i]._headers;
					
						write(i,lop.c_str(),lop.size());
						if (!Responsemap[i]._body_path.empty())
						{
							lop.erase();
							char *buffer = (char *)malloc(sizeof(char) * (Responsemap[i]._content_length + 1));
							int fd = open(Responsemap[i]._body_path.c_str(),  O_RDWR,  0666);
							read (fd, buffer,Responsemap[i]._content_length);
							write(i,buffer, Responsemap[i]._content_length);
							close(fd);
							free(buffer);
							//write(i,)
						}
						else if (!Responsemap[i]._tmp_file_path.empty()){
							lop.erase();
							char *buffer = (char *)malloc(sizeof(char) * (Responsemap[i]._content_length + 1));
							int fd = open(Responsemap[i]._tmp_file_path.c_str(),  O_RDWR,  0666);
							read (fd, buffer,Responsemap[i]._content_length);
							write(i,buffer, Responsemap[i]._content_length);
							close(fd);
							free(buffer);
							remove(Responsemap[i]._tmp_file_path.c_str());

						}
	//	re								
							FD_CLR(i,&writefds);
							FD_SET(i, &readsfds);
					}
				}


			}
		}
		}
	//FD_ISSET(i, &readsfds) || FD_ISSET(i,&writefds))
	//

	//
	//
	//		if (FD_ISSET(3, &readsfds) )
	//		{
	//			new_socket = accept(lopserver[3].fd, (struct sockaddr*)&lopserver[3].address, (socklen_t*)&lopserver[3].addrlen);
	//			req.set_socketid(new_socket);
	//			Requestsmap[new_socket] = req;
	//			FD_SET(new_socket,&master);
	//			if (new_socket > max_sd)
	//				max_sd = new_socket;
	//		}
	//		for (int i = 0; i < max_sd + 1; i++)
	//{
	//	if (FD_ISSET(i, &readsfds) || FD_ISSET(i,&writefds))
	//	{
	//		//else
	//		//{
	//				if (FD_ISSET(i, &readsfds))
	//				{
	//					 valread = read( i , buffer, BUFFERSIZE);
	//						buffer[valread] = '\0';
	//			for (std::map<int, Request>::iterator it = Requestsmap.begin(); it != Requestsmap.end(); ++it)
	//			{
	//				if (it->first == i)
	//				{
	//				//	if (it->second.)
	//					if (it->second.get_requestiscomplete() == true)
	//					{
	//						Response res;
	//					}
	//				//	it->second.adddata(buffer, valread);
	//				//	//std::cout<<" i m heree ------------ "<< sd<<std::endl;
	//					it->second.parserequest(buffer, valread);
	//				//}
	//			}
	//				}
	//		//}
	//	}
	//	}
			//if fd isset i read ||  fd isset i write
			/*
			{
				if i is server socket fd  
					then it is a new connection must be accptedd 
				else
				{
					wash read
						shuf lklian ash bgha 
					wash write
						jawb lkliyan 
				}
			}
			else docvnothing

			*/
		
	//if (FD_ISSET(i, &readsfds))
	//{
	//	new_socket = accept(lopserver[i].fd, (struct sockaddr*)&lopserver[i].address, (socklen_t*)&lopserver[i].addrlen);
	//	req.set_socketid(new_socket);
	//	Requestsmap[new_socket] = req;
	//	//printf("Hello message sent\n");
	//		for(int i = 0 ;i < 30;i++)
	//		{
	//			if (clientsocket[i] == 0)
	//			{
	//				clientsocket[i] = new_socket;
	//				break;
	//			}
	//		}
	//}
	//	      //else its some IO operation on some other socket
	//
	//for (int i = 0; i < 30; i++)  
    //{  
	//	////std::cout << "DBG__FOR__LOOP" << std::endl;
    //    
	//	sd = clientsocket[i];  
	//		////std::cout<<"allo"<<std::endl;
    //    if (FD_ISSET( sd , &readsfds))  
    //    {  
	//		////std::cout << "CONDITION__00" << std::endl;
	//		std::map<int, Request>::iterator it;
    //        //Check if it was for closing , and also read the 
    //        //incoming message 
    //        // if ((valread = read( sd , buffer, BUFFERSIZE)) == 0)  
    //        valread = read( sd , buffer, BUFFERSIZE);
	//		buffer[valread] = '\0';
    //        //std::cout << "RET_READ : " << valread << std::endl;
	//		if (valread < 10)
	//			//std::cout << "EXCEPTION : [" << buffer << "]" << std::endl;
	//		readpo += valread;
	//		 //std::cout << "ALL SIZR: " << readpo<< std::endl;
	//		if (valread == 0)  
    //        {  
	//			
	//			
    //            //Somebody disconnected , get his details and print 
    //            getpeername(sd , (struct sockaddr*)&address , \
    //                (socklen_t*)&addrlen);  
    //            printf("Host disconnected , ip %s , port %d \n" , 
    //                  inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
    //                 
    //            //Close the socket and mark as 0 in list for reuse 
    //            close( sd );  
	//			
    //            clientsocket[i] = 0;  
    //        }  
    //        else 
    //        {  
	//		////std::cout << "CONDITION__01" << std::endl;
	//			std::string str2;
	//	////std::cout<<str2.append(buffer)<<std::endl;
	//		//	write(wahedl9laoui,buffer,valread);
    //            buffer[valread] = '\0';  
	//			for (std::map<int, Request>::iterator it = Requestsmap.begin(); it != Requestsmap.end(); ++it)
	//			{
	//				if (it->first == sd)
	//				{
	//				//	if (it->second.)
	//					if (it->second.get_requestiscomplete() == true)
	//					{
	//						Response res;
	//					//res = server_response(req,server);
	//					//res._headers;
	//					//if (!res._tmp_file_path.empty())
	//					//{
	//					//	//reading nd remove
	//					//	res._tmp_file_path;
	//					//}
	//					//if (!res._body_path.empty())
	//					//{
	//					//	res._body_path();
	//					//}
	//					}
	//				//	it->second.adddata(buffer, valread);
	//				//	//std::cout<<" i m heree ------------ "<< sd<<std::endl;
	//					it->second.parserequest(buffer, valread);
	//				}
	//			}
	//			str2.erase();
    //            //send(sd , buffer , strlen(buffer) , 0 );
	//	  
    //        }
	//		////std::cout << "CONDITION__02" << std::endl;
    //    }  
    //} 
	//}
}
}
	
void				Webserver::webservbuild()
{
	ConfigParser parser;
	Root r;
	int opt = 1;
	r = parser.Rootparser(path);
	Server ser;
	servers = r.get_servers();
	int new_socket;
	int addrlen;
	int sockfd;
	struct sockaddr_in address;
	fd_set readsfds;
	int c = 0;
	int valread = 0; 
	FD_ZERO(&readsfds);          // change master 
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
		Myserver ser;
		ser.port = it->get_listenPort();
		ser.ipaddress = it->get_listenAddress();
		addrlen = sizeof(address);
		sockfd = socket(PF_INET,SOCK_STREAM,0); 
		ser.fd = sockfd;
		ser.index = c;
		FD_SET(sockfd, &master);  // shoukd have a mster readset 
		setsockopt(sockfd ,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(it->get_listenAddress().c_str());
		address.sin_port = htons(it->get_listenPort());
		ser.address = address;
		ser.addrlen = addrlen;
		lopserver[sockfd] = ser;
		bind(sockfd, (struct sockaddr*)&address, sizeof(address));
		listen(sockfd, 3);
		c++;
	}

}			

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */