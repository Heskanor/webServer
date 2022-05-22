#include "root.hpp"

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

void Root::parse_servers(std::string file)
{
    std::ifstream ifs(file);
    std::string line;
    std::string server_name;
    std::string root;
    int port;
    int bodySizeLimit;
    std::vector<Location> locations;
    std::vector<std::string> index;
    bool autoIndex;
    std::string error500;
    std::string error502;
    std::string upload_directory;
    std::vector<std::string> allowed_methods;
    std::string cgi_path;
    std::vector<std::string> cgi_ext;

    while (std::getline(ifs, line))
    {
        if (line.find("server_name") != std::string::npos)
        {
            server_name = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
        }
        else if (line.find("root") != std::string::npos)
        {
            root = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
        }
        else if (line.find("port") != std::string::npos)
        {
            port = std::stoi(line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1));
        }
        else if (line.find("bodySizeLimit") != std::string::npos)
        {
            bodySizeLimit = std::stoi(line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1));
        }
        else if (line.find("autoIndex") != std::string::npos)
        {
            autoIndex = std::stoi(line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1));
        }
        else if (line