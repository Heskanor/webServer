#include "location.hpp"
#include <iostream>
#include <string>


Location::Location()
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

void set_cgi_ext(std::vector<std::string> cgi_ext)
{
    _cgi_ext = cgi_ext;
}