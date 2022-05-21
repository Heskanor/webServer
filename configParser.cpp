#include "configParser.hpp"
#include <iostream>
#include <string>
#include <fstream>
//webserv config file parser
ConfigParser::ConfigParser()
{
    _current_line = "";
    _cursor = "";
    _current_key = "";
    _previous_key = "";
}

void ConfigParser::set_current_line(std::string line)
{
    _current_line = line;
}

void ConfigParser::set_cursor(std::string cursor)
{
    _cursor = cursor;
}

void ConfigParser::set_current_key(std::string key)
{
    _current_key = key;
}

void ConfigParser::set_previous_key(std::string key)
{
    _previous_key = key;
}

std::string ConfigParser::get_current_key()
{
    return _current_key;
}

std::string ConfigParser::get_current_line()
{
    return _current_line;
}

std::string ConfigParser::get_cursor()
{
    return _cursor;
}

std::string ConfigParser::get_previous_key()
{
    return _previous_key;
}

Server * parser(std::string file)
{
    
}