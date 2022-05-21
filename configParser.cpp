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

Server * parser(std::string file)
{
    ConfigParser *cp = new ConfigParser();
    Server *s = new Server();
    std::ifstream configFile(file);
    if (configFile.is_open())
    {
        while (getline(configFile, cp->_current_line))
        {
            cp->_cursor = cp->_current_line.substr(0, cp->_current_line.find(" "));
            if (cp->_cursor == "server_name")
            {
                cp->_current_key = cp->_current_line.substr(cp->_current_line.find(" ") + 1, cp->_current_line.length());
                s->server_name = cp->_current_key;
            }
            else if (cp->_cursor == "auto_index")
            {
                cp->_current_key = cp->_current_line.substr(cp->_current_line.find(" ") + 1, cp->_current_line.length());
                if (cp->_current_key == "on")
                    s->_autoIndex = true;
                else
                    s->_autoIndex = false;
            }
            else if (cp->_cursor == "root")
            {
                cp->_current_key = cp->_current_line.substr(cp->_current_line.find(" ") + 1, cp->_current_line.length());
                s->_root = cp->_current_key;
            }
            else if (cp->_cursor == "port")
            {
                cp->_current_key = cp->_current_line.substr(cp->_current_line.find(" ") + 1, cp->_current_line.length());
                s->_port = atoi(cp->_current_key.c_str());
            }
            else if (cp->_cursor == "body_size_limit")
            {
                cp->_current_key = cp->_current_line.substr(cp->_current_line.find(" ") + 1, cp->_current_line.length());
                
}