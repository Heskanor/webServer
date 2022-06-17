#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/wait.h>
#include <fcntl.h>
#include "cgi.hpp"


Cgi::Cgi(std::string path, std::vector<std::string> ext)
{
    int fd; 
    
    fd = open(path.c_str(), O_RDONLY);
    if (fd == -1)
        throw std::runtime_error("Cgi::Cgi: open failed");
    close(fd);
    if (ext.size() == 0)
        throw std::runtime_error("Cgi::Cgi: no extension");
    
    _path = path;
    _ext = ext;
}

Cgi::~Cgi()
{
}

std::string Cgi::getPath()
{
    return _path;
}

std::vector<std::string> Cgi::getExt()
{
    return _ext;
}
void Cgi::setPath(std::string path)
{
    _path = path;
}

void Cgi::setExt(std::vector<std::string> ext)
{
    _ext = ext;
}

bool Cgi::isCgi(std::string path) const
{
    std::string exx;

    if(path.find(".") == std::string::npos)
        return false;
    exx = path.substr(path.find_last_of(".") + 1);// not sure aboout that +1
    if (std::find(_ext.begin(), _ext.end(), exx) != _ext.end())
        return true;
    return false;
}

void Cgi::envMaker(Request *request)
{
    std::string line;
}

