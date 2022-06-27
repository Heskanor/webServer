#include "server.hpp"
#include "location.hpp"
#include "root.hpp"
#include <sstream> 

Server::Server()
{
    _listenPort = 80;
    _listenAddress = "0.0.0.0";
}

Server::Server(Root &src)
{
    _index = src.get_index();
    _root = src.get_root();
    _bodySizeLimit = src.get_bodySizeLimit();
    _autoIndex = src.get_auto_index();
    _error_map = src.get_errors_map();
    _uploadDirectory = src.get_upload_directory();
    _allowedMethods = src.get_allowed_methods();
}

Server::~Server()
{

}

Server::Server(const Server &src)
{
    *this = src;
}


Server &Server::operator=(Server const & rhs)
{
    Root::operator=(rhs);
    _server_name = rhs._server_name;
    _listenPort = rhs._listenPort; 
    _listenAddress = rhs._listenAddress;
    _locations = rhs._locations;
    _redirection = rhs._redirection;

    return *this;
}

//seters
void Server::set_server_name(std::vector<std::string> name)
{
    _server_name = name;
}

std::vector<std::string> Server::get_server_name()
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

std::pair<std::string, std::string> Server::get_redirection()
{
    return _redirection;
}

void Server::set_redirection(std::string code, std::string url)
{
    _redirection.first = code;
    _redirection.second = url;
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

void Server::clear(Root &src)
{
    _server_name.clear();
    _listenAddress.clear();
    _listenPort = 0;
    _locations.clear();
    _redirection.first.clear();
    _redirection.second.clear();
    _index = src.get_index();
    _root = src.get_root();
    _bodySizeLimit = src.get_bodySizeLimit();
    _autoIndex = src.get_auto_index();
    _error_map = src.get_errors_map();
    _uploadDirectory = src.get_upload_directory();
    _allowedMethods = src.get_allowed_methods();
}

bool Server::check_empty()
{
    if (_server_name.empty() || (_locations.empty() && _root.empty()))
        return true;
    else
        return false;
}

void Server::insert_location(Location &location)
{
	_locations.insert(_locations.begin(), location);
}