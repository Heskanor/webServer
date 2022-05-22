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

int Server::get_port()
{
    return _port;
}

void Server::add_location(Location location)
{
    _locations.push_back(location);
}

std::vector<Location> Server::get_locations()
{
    return _locations;
}
