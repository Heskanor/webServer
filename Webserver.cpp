#include "Webserver.hpp"
#define BUFFERSIZE 5000
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
	fd_set	readsfds;
	fd_set	writefds;
	char 	*buffer = (char *)malloc(sizeof(char) * (BUFFERSIZE));
	int	 	valread = 0;
	int 	fd = -1;;
	FD_ZERO(&readsfds);
	FD_ZERO(&writefds);
	int 	new_socket ;
	char 	*buffer4;
	Request req;
	int 	checker = 0;
	int 	activ;
	int 	max_sd = -1;
	std::map<int,Myserver>::iterator it;
	for(std::map<int,Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
	{
		if (it->second.fd > max_sd)
			max_sd = it->second.fd;
	}
	while (true)
	{

		readsfds =  master ;
		writefds = master2;
		activ = select(max_sd + 1, &readsfds, &writefds, NULL, NULL);
		for (int i =0; i < max_sd + 1; i++)
		{
			if (FD_ISSET(i, &readsfds) || FD_ISSET(i,&writefds))
			{
				if (checkifisserver(i) == true)
				{
					hoole++;
					new_socket = accept(lopserver[i].fd, (struct sockaddr*)&lopserver[i].address, (socklen_t*)&lopserver[i].addrlen);
					req.set_socketid(new_socket);
					if (hoole == 2)
					{
						std::cout<<"DsadsaDAS"<<std::endl;
					}
					req.set_timeout(time_now());
					for(std::map<int,Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
					{
						std::cout<<"i really here"<<std::endl;
						if (it->second.fd == i)
						{
							req.setserver_fd(it->second.index);
							std::cout<<it->second.index<<"|||||||||||"<<std::endl;
						}
					}
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
						std::string op;
						op.append(buffer);
						std::cout<<time_now() - Requestsmap[i].get_timeout()<<std::endl;
						if (valread > 0 && Requestsmap[i].get_requestiscomplete() == true)
						{
							Request req2;
							Requestsmap[i] = req2;
						}
						if (valread == -1)
						{
							FD_CLR(i,&readsfds);
							FD_CLR(i,&master);
							close(i);
						}
						else if(valread == 0  && ((time_now() - Requestsmap[i].get_timeout()) >5000))
						{
							FD_CLR(i,&readsfds);
							close(i); 
						}
						else
						{
							for (std::map<int, Request>::iterator it = Requestsmap.begin(); it != Requestsmap.end(); ++it)
							{
								if (it->first == i)
								{
									it->second.parserequest(buffer, valread);
									//free(buffer);
									Requestsmap[i].set_timeout(time_now());
									if (it->second.get_requestiscomplete() == true)
									{
										std::cout<<" im here "<<std::endl;
										std::cout<<Requestsmap[i].get_requestur()<<std::endl;
										Response resp;
										std::cout<<req.getserver_fd()<<std::endl;
										resp = server_response(it->second,servers[req.getserver_fd()]);
										Responsemap[it->first] = resp;
										FD_CLR(it->first,&master);
										FD_SET(it->first, &writefds);
										FD_SET(it->first, &master2);											//	Requestsmap.erase(i);

									}
							}
						}
				}
					}
				if (FD_ISSET(i, &writefds) && Responsemap[i]._Responecomplete == 0)
				{
					std::string lop;
					int n = 0;
					int rest = 0;
					std::string path;
					if (!Responsemap[i]._body_path.empty())
					{
						path = Responsemap[i]._body_path;
					}
					else if (!Responsemap[i]._tmp_file_path.empty())
					{
						path = Responsemap[i]._tmp_file_path;
					}
					if (Responsemap[i].sentheader == 0)
					{

						fd = open(path.c_str(),  O_RDONLY,  0666);
						lop = Responsemap[i]._headers;
						Responsemap[i].headersize = lop.size();
						Responsemap[i].sentheader = 1;
						Responsemap[i]._content_length += lop.size();
					}
					else if((Responsemap[i]._content_length - Responsemap[i].homuchiwrite) >= BUFFERSIZE)
					{
							char buffer4[BUFFERSIZE + 1];
							n = read (fd, buffer4, BUFFERSIZE);
							buffer4[n] = '\0';
							std::string tmp(buffer4, n);
							lop = tmp;
							// free(buffer4);
					}
					else
				{
						char buffer4[BUFFERSIZE + 1];
						n = read(fd, buffer4, BUFFERSIZE);
						buffer4[n] = '\0';
						Responsemap[i]._Responecomplete = 1;
						std::string tmp(buffer4, n);
						lop = tmp;
						// free(buffer4);
					}
					// std::cout<<"im printing hereeee "<<std::endl;
					ssize_t sent_bytes = write(i, lop.c_str(),lop.size());
					// std::cout << "send bytes : " << sent_bytes<< std::endl;
					Responsemap[i].homuchiwrite += sent_bytes;
					// std::cout<<"Response :"<<Responsemap[i].homuchiwrite<<"|||"<<Responsemap[i]._content_length<<std::endl;
					if (Responsemap[i]._Responecomplete == 1)
					{
						// //std::cout<<"Response :"<<Responsemap[i].homuchiwrite<<std::endl;
					FD_CLR(i,&master2);
					//FD_CLR(i,&writefds);
					FD_SET(i, &master);
						close (fd);
					//close(i);									
					}
				}
				}
				}
		}
		}
	}


	

int 			Webserver::checkingservers(std::vector<Server> lop, Request req)
{
    std::vector<int> op;
    int i =0;
    int size = 0;
    int storingi = -1;
    
    for (int i = 0;i < lop.size();i++)
    {
        if (lop[i].get_listenAddress() == req.get_ip() && std::to_string(lop[i].get_listenPort()) == req.get_port())
        {
            //std::cout<<"----"<<i<<"---"<<std::endl;
            //std::cout<<lop[i].get_listenAddress()<<std::endl;
            //std::cout<<lop[i].get_listenPort()<<std::endl;
            //std::cout<<req.get_port()<<std::endl;
            //std::cout<< req.get_ip()<<std::endl;
            op.push_back(i);
        }
    }
    if (op.empty() == false)
    {
        for (int i = 0; i < op.size(); i++)
        {
            for (int j = 0; j < lop.size(); j++)
            {
                if (op[i] == j)
                {
					if (lop[i].get_server_name().empty() == false)
					{
						for (int c = 0; c < lop[i].get_server_name().size();c++ )
						{
							if (lop[i].get_server_name()[c] == req.get_ip())
							{
								return op[i];
							}
						}
					}
                }
            }
        }
		return op[0]; 
    }
    return 0;
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
		setsockopt(sockfd ,SOL_SOCKET,SO_REUSEADDR , &opt, sizeof(opt));
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

