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

void Server::set_root(std::string root)
{
    _root = root;
}

void Server::set_index(std::vector<std::string> index)
{
    _index = index;
}

void Server::set_auto_index(bool autoIndex)
{
    _auto_index = autoIndex;
}

void Server::set_error500(std::string error500)
{
    _error500 = error500;
}

void Server::set_error502(std::string error502)
{
    _error502 = error502;
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

std::string Server::get_root()
{
    return _root;
}

std::vector<std::string> Server::get_index()
{
    return _index;
}

bool Server::get_auto_index()
{
    return _auto_index;
}

std::string Server::get_error500()
{
    return _error500;
}

std::string Server::get_error502()
{
    return _error502;
}

void Server::set_location(Location *location)
{
    _location = location;
}

Location *Server::get_location()
{
    return _location;
}