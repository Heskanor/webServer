#include "server.hpp"
#include "location.hpp"

Server::Server()
{

}

Server::~Server()
{

}

Server &Server::operator=(Server const & rhs)
{
    return *this;
}

//seters
void Server::set_server_name(std::string name)
{
    _server_name = name;
}
void Server::set_port(int port)
{
    _port = port;
}

// geters
std::string Server::get_host()
{
    return _host;
}

int Server::get_port()
{
    return _port;
}

void Server::set_location(Location *location)
{
    _locations = location;
}

Location *Server::get_location()
{
    return _locations;
}