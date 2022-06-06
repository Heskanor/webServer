#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include "Client.hpp"
# include "MiniRequest.hpp" 

class Response
{
	public:
		Response(void);
		~Response(void);

		std::string		getResponse(void);
		void			setResponse(std::string);
	
	private:
		std::string		_response;

};

void send_400(Client* client);
void send_404(Client* client);
void serve_resource(Client* client, std::string resource);

#endif