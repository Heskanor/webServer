#ifndef MINIREQUEST_HPP
# define MINIREQUEST_HPP

#include <iostream>

typedef struct miniRequest {
	std::string method;
	std::string ipaddress;
	std::string port;
	std::string thhpversion;
	std::string host;
	bool thereistraansfer;
	std::string requestur;
	bool Connection;
	bool transferchunks;
	std::string content_type;
	std::string  content_lenght;
} MiniRequest;

#endif