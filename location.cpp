#include "location.hpp"
#include <iostream>
#include <string>
#include "location.hpp"
#include "server.hpp"
#include "root.hpp"

Location::Location()
{
}

Location::Location(const Location &src)
{
    *this = src;
}

Location::Location(Server &src)
{
    _index = src.get_index();
    _root = src.get_root();
    _bodySizeLimit = src.get_bodySizeLimit();
    _autoIndex = src.get_auto_index();
    _error_map = src.get_errors_map();
    _uploadDirectory = src.get_upload_directory();
    _allowedMethods = src.get_allowed_methods();
    _redirection = src.get_redirection();
}

Location &Location::operator=(Location const & rhs)
{
    _index = rhs._index;
   _root = rhs._root;
   _bodySizeLimit = rhs._bodySizeLimit;
   _autoIndex = rhs._autoIndex;
   _error_map = rhs._error_map;
   //std::cout << "3aalaaam :"<< _error_map["399"]<<std::endl;
   _uploadDirectory = rhs._uploadDirectory;
   _allowedMethods = rhs._allowedMethods;
   _redirection = rhs._redirection;
    _path = rhs._path;
    _cgi_path = rhs._cgi_path;
    _cgi_ext = rhs._cgi_ext;

    return *this;
}

Location::~Location()
{
}

//geters seters
std::string Location::get_path()
{
    return _path;
}

void Location::set_path(std::string path)
{
    _path = path;
}

std::string Location::get_cgi_path()
{
    return _cgi_path;
}

void Location::set_cgi_path(std::string cgi_path)
{
    _cgi_path = cgi_path;
}

std::vector<std::string> Location::get_cgi_ext()
{
    return _cgi_ext;
}

void Location::set_cgi_ext(std::vector<std::string> cgi_ext)
{
    _cgi_ext = cgi_ext;
}
void Location::clear(Server &src)
{
    // Server::clear();
    _path = "/";
    _cgi_path = "";
    _cgi_ext.clear();
    _index = src.get_index();
    _root = src.get_root();
    _bodySizeLimit = src.get_bodySizeLimit();
    _autoIndex = src.get_auto_index();
    _error_map = src.get_errors_map();
    _uploadDirectory = src.get_upload_directory();
    _allowedMethods = src.get_allowed_methods();
    _redirection = src.get_redirection();
}
bool Location::check_lempty()
{
    if (_path.empty())
        return true;
    else
        return false;
}