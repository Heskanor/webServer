#include "root.hpp"
#include "server.hpp"
#include "location.hpp"

Root::Root()
{

}

Root::~Root()
{

}

Root &Root::operator=(Root const & rhs)
{
    return *this;
}

void Root::set_root(std::string root)
{
    _root = root;
}

void Root::set_index(std::vector<std::string> index)
{
    _index = index;
}

void Root::set_auto_index(bool autoIndex)
{
    _auto_index = autoIndex;
}

std::string Root::get_root()
{
    return _root;
}

std::vector<std::string> Root::get_index()
{
    return _index;
}

bool Root::get_auto_index()
{
    return _auto_index;
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

void set_servers(std::vector<Server> servers)
{
    _servers = servers;
}
void add_server(Server server)
{
    _servers.push_back(server);
}
