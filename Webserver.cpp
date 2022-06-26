#include "Webserver.hpp"
#define BUFFERSIZE 5000
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>    //close
#include <arpa/inet.h> //close
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

Webserver::Webserver(const Webserver &src)
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

Webserver &Webserver::operator=(Webserver const &rhs)
{
    lopserver = rhs.lopserver;
    Requestsmap = rhs.Requestsmap;
    master = rhs.master;
    path = rhs.path;
    return *this;
}

// std::ostream &operator<<(std::ostream &o, Webserver const &i)
// {
//     // o << "Value = " << i.getValue();
//     return o;
// }

/*
 ** --------------------------------- METHODS ----------------------------------
 */
bool Webserver::checkifisserver(int i)
{
    for (std::map<int, Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
    {
        if (it->second.fd == i)
            return true;
    }
    return (false);
}
bool Webserver::checkifitsfdserver(int i)
{
    for (std::map<int, Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
    {
        if (it->second.fd == i)
            return true;
    }
    return false;
}

void Webserver::Runmywebserver()
{
    fd_set readsfds;
    fd_set writefds;
    char *buffer = (char *)malloc(sizeof(char) * (BUFFERSIZE) + 1);
    int valread = 0;
    std::string lop;
    int fd = -1;
    FD_ZERO(&readsfds);
    FD_ZERO(&writefds);
    int new_socket;
    // char *buffer4;
    // int po;
    Request req;
    // int checker = 0;
    int activ;
    int max_sd = -1;
    std::map<int, Myserver>::iterator it;
    for (std::map<int, Myserver>::iterator it = lopserver.begin(); it != lopserver.end(); it++)
    {
        if (it->second.fd > max_sd)
            max_sd = it->second.fd;
    }
    while (true)
    {
        std::cout<<" a zaaaaaaaaaabo"<<std::endl;
        readsfds = master;
        writefds = master2;
       if ( (activ = select(max_sd + 1, &readsfds, &writefds, NULL, NULL)) == -1)
       {
            std::cout <<"Aaaaay  Zeeeeeeeeekiiiiiiiiiii"<<std::endl;
            continue;
       }

        for (int i = 0; i < max_sd + 1; i++)
        {
            if (FD_ISSET(i, &readsfds) || FD_ISSET(i, &writefds))
            {
                if (checkifisserver(i) == true)
                {
                    new_socket = accept(lopserver[i].fd, (struct sockaddr *)&lopserver[i].address, (socklen_t *)&lopserver[i].addrlen);
                    //std::cout << "cnx fd : " << new_socket << std::endl;
                    req.set_socketid(new_socket);
                    Requestsmap[new_socket] = req;
                    FD_SET(new_socket, &master);
                    if (new_socket > max_sd)
                        max_sd = new_socket;
                }
                else 
                {
                    if (FD_ISSET(i, &readsfds))
                    {
                        if ((valread = read(i, buffer, BUFFERSIZE)) <= 0)
                        {
                            FD_CLR(i, &master);
                            close(i);
                        }
                        else
                        {
                            buffer[valread] = '\0';
                            if (Requestsmap[i].get_requestiscomplete() == true)
                            {
                                Requestsmap.erase(i);
                                Request req2;
                                Requestsmap[i] = req2;
                            }
                            for (std::map<int, Request>::iterator it = Requestsmap.begin(); it != Requestsmap.end(); ++it)
                            {
                                if (it->first == i)
                                {
                                    it->second.parserequest(buffer, valread);
                                    if (it->second.get_requestiscomplete() == true)
                                    {
                                        //std::cout << Requestsmap[i].get_requestur() << std::endl;
                                        Response resp;
                                        resp = server_response(it->second, servers[2]);
                                        Responsemap[it->first] = resp;
                                     //   Requestsmap.erase(it->first);
                                        FD_CLR(i, &master);
                                        FD_SET(i, &writefds);
                                        FD_SET(i, &master2);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (FD_ISSET(i,&writefds))
                    {
                        if (Responsemap[i].sentheader == 0)
                        {
                            Responsemap[i].lop = Responsemap[i]._headers;
                            Responsemap[i].sentheader = 1;
                            Responsemap[i].onlypath = checkingpath(Responsemap[i]);
                            Responsemap[i]._content_length += Responsemap[i].lop.size();
                            if (Responsemap[i].onlypath.empty() == false)
                                Responsemap[i].fd = open(Responsemap[i].onlypath.c_str(), O_RDONLY, 0666);

                        }
                        else
                        {
                            if (Responsemap[i]._content_length == Responsemap[i].homuchiwrite)
                            {
                                Responsemap[i]._Responecomplete = 1;
				    			FD_CLR(i, &master2);
				    			if (Responsemap[i].onlypath.empty() == false)
				    			     close(Responsemap[i].fd);
                                 Responsemap.erase(i);
                                 close (i);
                                std::cerr << " ###### : " << fd << std::endl;
                            }
                            else if ((Responsemap[i]._content_length > Responsemap[i].homuchiwrite))
                            {
                                char  *buffer4 = (char*)malloc(BUFFERSIZE + 1);
				    			int n = read(Responsemap[i].fd, buffer4, BUFFERSIZE);
                                std::cout<<"aloooooooooooooooooo"<<std::endl;
				    			if (n >= 0)
                                {
                             std::cout<<"aloooooooooooooooooo22"<<std::endl;

                                         buffer4[n] = '\0';
				    			std::string tmp(buffer4, n);
				    			Responsemap[i].lop += tmp;
				    			free(buffer4);
                                }
                           
                            }   
                        }
                        if (Responsemap[i]._Responecomplete == 0)
                        {
                            size_t sent_bytes;
				    		if ( (sent_bytes = write(i, Responsemap[i].lop.c_str(), Responsemap[i].lop.size())) <= 0)
				    		{
				    			FD_CLR(i, &master2);
				    			close(i);
				    			
				    			if (Responsemap[i].onlypath.empty() == false)
                                {
                                    std::cerr << " If cond : " <<Responsemap[i].fd<< std::endl; 
				    				 close(Responsemap[i].fd);
                                }
                                Responsemap.erase(i);
				    		}
                            if (sent_bytes < Responsemap[i].lop.size())
				    		{
				    			Responsemap[i].lop = Responsemap[i].lop.substr(sent_bytes);
				    		}
				    		else
				    			Responsemap[i].lop.clear();
                            Responsemap[i].homuchiwrite += sent_bytes;
                        }
                    }
                }
            }
        }
    }
}

std::string     Webserver::checkingpath(Response &res)
{
    std::string path;
    if (!res._body_path.empty())
	{
		return (res._body_path);
	}
	else if (!res._tmp_file_path.empty())
	{
		return (res._tmp_file_path);
	}
    return path;
}
int Webserver::checkingservers(std::vector<Server> lop, Request req)
{
    std::vector<size_t> op;
    // int storingi = -1;

    for (size_t i = 0; i < lop.size(); i++)
    {
        if (lop[i].get_listenAddress() == req.get_ip() && std::to_string(lop[i].get_listenPort()) == req.get_port())
        {
            // //std::cout<<"----"<<i<<"---"<<std::endl;
            // //std::cout<<lop[i].get_listenAddress()<<std::endl;
            // //std::cout<<lop[i].get_listenPort()<<std::endl;
            // //std::cout<<req.get_port()<<std::endl;
            // //std::cout<< req.get_ip()<<std::endl;
            op.push_back(i);
        }
    }
    if (op.empty() == false)
    {
        for (size_t i = 0; i < op.size(); i++)
        {
            for (size_t j = 0; j < lop.size(); j++)
            {
                if (op[i] == j)
                {
                    if (lop[i].get_server_name().empty() == false)
                    {
                        for (size_t c = 0; c < lop[i].get_server_name().size(); c++)
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
void Webserver::webservbuild()
{
    ConfigParser parser;
    Root r;
    int opt = 1;
    r = parser.Rootparser(path);
    Server ser;
    servers = r.get_servers();
    // int new_socket;
    int addrlen;
    int sockfd;
    struct sockaddr_in address;
    fd_set readsfds;
    int c = 0;
    // int valread = 0;
    FD_ZERO(&readsfds); // change master
    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        Myserver ser;
        ser.port = it->get_listenPort();
        ser.ipaddress = it->get_listenAddress();
        addrlen = sizeof(address);
        sockfd = socket(PF_INET, SOCK_STREAM, 0);
        //std::cout << "Socketa fd : " << sockfd << std::endl;
        ser.fd = sockfd;
        ser.index = c;
        FD_SET(sockfd, &master); // shoukd have a mster readset
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(it->get_listenAddress().c_str());
        address.sin_port = htons(it->get_listenPort());
        ser.address = address;
        ser.addrlen = addrlen;
        lopserver[sockfd] = ser;
        bind(sockfd, (struct sockaddr *)&address, sizeof(address));
        listen(sockfd, 128);
        c++;
    }
}

/*
 ** --------------------------------- ACCESSOR ---------------------------------
 */
