#ifndef MYSERVER_HPP
# define MYSERVER_HPP

# include <iostream>
# include <string>
#include <netinet/in.h>
#include <sys/select.h>
#include <map>
class Myserver
{

	public:

		Myserver();
		Myserver( Myserver const & src );
		~Myserver();

		Myserver &		operator=( Myserver const & rhs );
		int port;
		std::string ipaddress;
		int fd;
		int index;
		struct sockaddr_in address;
		int addrlen;
	private:

};

//std::ostream &			operator<<( std::ostream & o, Myserver const & i );

#endif /* ******************************************************** MYSERVER_H */