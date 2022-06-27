#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

//#include "webser.hpp"
#include "Myserver.hpp"
#include "Request.hpp"
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <sstream>  
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include "configParser.hpp"
#include "Response.hpp"
#include <netinet/in.h> 
#include <sys/time.h>
#include "root.hpp"
# include <sys/time.h>

#include "server.hpp"
class Webserver
{

	public:

		Webserver(std::string _path);
		Webserver( Webserver const & src );
		~Webserver();
		int hoole;
		void webservbuild();
		void Runmywebserver();
		bool checkifitsfdserver(int i);
		std::string checkingpath(Response &res);
		Server checkingservers(std::vector<Server> lop, Request req);
		bool checkifisserver(int i);
		long	int	time_now(void)
		{
			struct timeval	right1;

			gettimeofday(&right1, NULL);
			return ((right1.tv_sec * 1000) + (long int)(right1.tv_usec / 1000));
		}
		fd_set master;
		fd_set master2;
		std::string path;
		std::map<int, Myserver> lopserver;
		std::vector<Server> servers ;
		std::map<int, Request> Requestsmap;
		std::map<int, Response> Responsemap;
		Webserver &		operator=( Webserver const & rhs );

	private:

};

// std::ostream &			operator<<( std::ostream & o, Webserver const & i );

#endif /* ******************************************************* WEBSERVER_H */
