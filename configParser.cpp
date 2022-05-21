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
    std::ifstream config_file;
    std::string line;
    config_file.open(file);
    if (config_file.is_open())
    {
        while (getline(config_file, line))
        {
            parser_line(line);
        }
        config_file.close();
    }
    else
    {
        std::cerr << "ERROR: Failed to open file" << std::endl;
    }
    return _server;
}

void parser_line(std::string line)
{
    ConfigParser config_parser;
    config_parser.set_current_line(line);
    config_parser.set_cursor("");
    config_parser.set_current_key("");
    config_parser.set_previous_key("");
    parser_config_line(config_parser);
}

void parser_config_line(ConfigParser config_parser)
{
    if (config_parser.get_current_line() == "")
        return;
    if (config_parser.get_cursor() == "")
    {
        if (config_parser.get_current_line()[0] == '#')
            return;
        if (config_parser.get_current_line()[0] == ' ')
            config_parser.set_cursor(config_parser.get_current_line().substr(1, config_parser.get_current_line().length()));
        else
            config_parser.set_cursor(config_parser.get_current_line());
    }
    if (config_parser.get_current_key() == "")
    {
        if (config_parser.get_cursor()[0] == ' ')
            config_parser.set_current_key(config_parser.get_cursor().substr(1, config_parser.get_cursor().length()));
        else
            config_parser.set_current_key(config_parser.get_cursor());
    }
    if (config_parser.get_current_key()[0] == '
}