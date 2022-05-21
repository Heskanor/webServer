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

std::vector<std::string> Location::get_index()
{
    return _index;
}

void Location::set_index(std::vector<std::string> index)
{
    _index = index;
}

bool Location::get_auto_index()
{
    return _auto_index;
}

void Location::set_auto_index(bool autoIndex)
{
    _auto_index = autoIndex;
}

std::string Location::get_error_map(int error)
{
    return _error_map[error];
}

void Location::set_error_map(int error, std::string error_message)
{
    _error_map[error] = error_message;
    //use this if you want to add more error messages
    //_error_map.insert(std::pair<int, std::string>(error, error_message));
    //_error_map.insert({error, error_message});
}

std::string Location::get_upload_directory()
{
    return _upload_directory;
}

void Location::set_upload_directory(std::string upload_directory)
{
    _upload_directory = upload_directory;
}

std::vector<std::string> Location::get_allowed_methods()
{
    return _allowed_methods;
}

void Location::set_allowed_methods(std::vector<std::string> allowed_methods)
{
    _allowed_methods = allowed_methods;
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

//methods
void Location::add_index(std::string index)
{
    _index.push_back(index);
}

void Location::add_allowed_method(std::string method)
{
    _allowed_methods.push_back(method);
}

