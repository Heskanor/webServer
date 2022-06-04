#include "root.hpp"
#include "server.hpp"
#include "location.hpp"

Root::Root()
{

}

Root::~Root()
{

}

Root::Root(const Root &src)
{
    *this = src;
}

Root &Root::operator=(Root const & rhs)
{
    _index = rhs._index;
    _servers = rhs._servers;
    _root = rhs._root;
    std::cout<<"sizee :"<<rhs._root<<std::endl;
    _bodySizeLimit = rhs._bodySizeLimit;
    _autoIndex = rhs._autoIndex;
    _error_map = rhs._error_map;
    _uploadDirectory = rhs._uploadDirectory;
    _allowedMethods = rhs._allowedMethods;
    return *this;
}

std::string Root::get_root()
{
    return _root;
}

void Root::set_root(std::string root)
{
    _root = root;
}

void Root::set_index(std::vector<std::string> index)
{
    _index = index;
}

std::vector<std::string> Root::get_index()
{
    return _index;
}

void Root::set_auto_index(bool autoIndex)
{
    _autoIndex = autoIndex;
}

bool Root::get_auto_index()
{
    return _autoIndex;
}

int Root::get_bodySizeLimit()
{
    
    return _bodySizeLimit;
}

void Root::set_bodySizeLimit(int bodySizeLimit)
{
    
    _bodySizeLimit = bodySizeLimit;
}

std::vector<Server> Root::get_servers()
{
    return _servers;
}

void Root::add_index(std::string index)
{
    _index.push_back(index);
}

void Root::set_servers(std::vector<Server> servers)
{
    _servers = servers;
}

Server Root::get_server(int index)
{
    return _servers[index];
}

void Root::add_server(Server &server)
{
    std::cout << "add server" << std::endl;
    std::cout << server.get_server_name() << std::endl;
    _servers.push_back(server);
    // std::cout << "push back not error" << std::endl;
    // print servers vector
    for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
    {
        std::cout <<"lol"<< it->get_server_name() << std::endl;
    }
}

std::string Root::get_error_map(std::string error)
{
    return _error_map[error];
}

void Root::add_error_map(std::string error, std::string error_url)
{
    _error_map[error] = error_url;
}

std::string Root::get_upload_directory()
{
    return _uploadDirectory;
}

void Root::set_upload_directory(std::string upload_directory)
{
    _uploadDirectory = upload_directory;
}

std::vector<std::string> Root::get_allowed_methods()
{
    return _allowedMethods;
}

void Root::set_allowed_methods(std::vector<std::string> allowed_methods)
{
    _allowedMethods = allowed_methods;
}


