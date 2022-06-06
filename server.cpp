#include "server.hpp"
#include "location.hpp"
#include "root.hpp"
#include <sstream> 

Server::Server()
{

}

Server::~Server()
{

}

Server::Server(const Server &src):
    _server_name(src._server_name),
    _listenAddress(src._listenAddress),
    _listenPort(src._listenPort),
    _locations(src._locations)
{
    *this = src;
}


Server &Server::operator=(Server const & rhs)
{
    _server_name = rhs._server_name;
    _listenAddress = rhs._listenAddress;
    _listenPort = rhs._listenPort;
    //_locations = rhs._locations;

    return *this;
}

//seters
void Server::set_server_name(std::string name)
{
    _server_name = name;
}

std::string Server::get_server_name()
{
    return _server_name;
}


void Server::set_listenPort(std::string port)
{
    std::stringstream ss;
    ss << port;
    ss >> _listenPort;
}

int Server::get_listenPort()
{
    return _listenPort;
}

void Server::set_listenAddress(std::string address)
{
    _listenAddress = address;
}

std::string Server::get_listenAddress()
{
    return _listenAddress;
}

std::map<std::string, std::string> Server::get_redirections()
{
    return _redirections;
}

std::string Server::get_redirection(std::string code)
{
    return _redirections[code];
}

void Server::add_redirect_map(std::string code, std::string url)
{
    _redirections[code] = url;
}

void Server::add_location(Location &location)
{
    _locations.push_back(location);
}

std::vector<Location> Server::get_locations()
{
    return _locations;
}

Location Server::get_location(int index)
{
    return _locations[index];
}
