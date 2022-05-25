#include "configParser.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <vector>
#include "location.hpp"

//webserv config file parser
ConfigParser::ConfigParser()
{

	this->_keys[0] = "index:";//str table
	this->_keys[1] = "root:";//str
	this->_keys[2] = "errors:";//map
	this->_keys[3] = "bodySizeLimit:";//int
    this->_keys[4] = "autoIndex:";//int
    this->_keys[5] = "uploadDirectory:";//str
    this->_keys[6] = "allowedMethods:";//str table
    this->_keys[7] = "cgiPath:";//str
    this->_keys[8] = "cgiExt:";//str table
    this->_keys[9] = "serverName:";//str
    this->_keys[10] = "listen:";//str port table
    this->_keys[12] = "redirection:";//str
    this->_keys[11] = "locations:";//str

	this->direcriveParser[0] = &ConfigParser::strTabParser;
    this->direcriveParser[1] = &ConfigParser::strParser;
    this->direcriveParser[2] = &ConfigParser::mapParser;
    this->direcriveParser[3] = &ConfigParser::intParser;
    this->direcriveParser[4] = &ConfigParser::intParser;
    this->direcriveParser[5] = &ConfigParser::strParser;
    this->direcriveParser[6] = &ConfigParser::strTabParser;
    this->direcriveParser[7] = &ConfigParser::strParser;
    this->direcriveParser[8] = &ConfigParser::strTabParser;
    this->direcriveParser[9] = &ConfigParser::strParser;
    this->direcriveParser[10] = &ConfigParser::strTabPortParser;
    this->direcriveParser[11] = &ConfigParser::strParser;
    this->direcriveParser[12] = &ConfigParser::strParser;

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

Root parser(std::string file)
{
    Root root;
    std::ifstream configFile(file);
    std::string line;
    std::string cursor;
    std::string current_key;   
    std::string previous_key;
    std::string current_line;
    std::string root_name;
    std::string token;
    std::vector<std::string> index;
    bool auto_index = false;
    int bodySizeLimit = 0;
    std::vector<Server> servers;
    size_t pos;
    if (configFile.is_open())
    {
        while (getline(configFile, line))
        {
            std::stringstream X(line);
            if (line.find("server:") == std::string::npos)
            {
                if ((pos = line.find("index:")) != std::string::npos)
                {
                    getline(X, token,' ');
                    while (getline(X, token,' '))
                    {
                        if (token != "")
                            root.add_index(token); //call index setter
                    }
                }
                else if ((pos = line.find("auto_index:")) != std::string::npos)
                {
                    getline(X, token,' ');
                    while (getline(X, token,' '))
                    {
                        if (token != "")
                        {
                            if (token.find("true") == std::string::npos && token.find("false") == std::string::npos)
                            {
                                std::cout << "Error: Auto-Index must be true or false" << std::endl;
                                exit(1);
                            }
                            else if (token.find("true") != std::string::npos)
                                root.set_auto_index(true);
                            else if (token.find("false") != std::string::npos)
                                root.set_auto_index(false);
                        }
                    }
                }
                else if ((pos = line.find("bodySizeLimit:")) != std::string::npos)
                {
                    getline(X, token,' ');
                    if (getline(X, token,' ') && (token.find_first_not_of("0123456789") == std::string::npos))
                        root.set_bodySizeLimit(std::stoi(token));
                    else
                    {
                        std::cout << "Error: BodySizeLimit must be a number" << std::endl;
                        exit(1);
                    }
                }
                if ((pos = line.find("root:")) != std::string::npos)
                {
                    getline(X, token,' ');
                    if (getline(X, token,' '))
                        root.set_root(token);
                    else
                    {
                        std::cout << "Error: Root must be a string" << std::endl;
                        exit(1);
                    }
                }
            }
            else
            {
                Server server;
                while (getline(configFile, line))
                {
                    if (token != "")
                    {
                        if (token.find("listen_port:") != std::string::npos)
                        {
                            getline(X, token,' ');
                            if (getline(X, token,' ') && (token.find_first_not_of("0123456789") == std::string::npos))
                                server.set_port(std::stoi(token));
                            else
                            {
                                std::cout << "Error: Port must be a number" << std::endl;
                                exit(1);
                            }
                        }
                        else if (token.find("root:") != std::string::npos)
                        {
                            getline(X, token,' ');
                            if (getline(X, token,' '))
                                server.set_root(token);
                            else
                            {
                                std::cout << "Error: Root must be a string" << std::endl;
                                exit(1);
                            }
                        }
                        else if (token.find("index:") != std::string::npos)
                        {
                            getline(X, token,' ');
                            while (getline(X, token,' '))
                            {
                                if (token != "")
                                    server.add_index(token); //call index setter
                            }
                        }
                        else if (token.find("auto_index:") != std::string::npos)
                        {
                            getline(X, token,' ');
                            while (getline(X, token,' '))
                            {
                                if (token != "")
                                {
                                    if (token.find("true") == std::string::npos && token.find("false") == std::string::npos)
                                    {
                                        std::cout << "Error: Auto-Index must be true or false" << std::endl;
                                        exit(1);
                                    }
                                }
                            }
                        }
                        else if(token.find("server_name:") != std::string::npos)
                        {
                            getline(X, token,' ');
                            if (getline(X, token,' '))
                                server.set_server_name(token);
                            else
                            {
                                std::cout << "Error: Server Name must be a string" << std::endl;
                                exit(1);
                            }
                        }
                        else if(token.find("bodySizeLimit:") != std::string::npos)
                        {
                            getline(X, token,' ');
                            if (getline(X, token,' ') && (token.find_first_not_of("0123456789") == std::string::npos))
                                server.set_bodySizeLimit(std::stoi(token));
                            else
                            {
                                std::cout << "Error: BodySizeLimit must be a number" << std::endl;
                                exit(1);
                            }
                        }
                        else if (token.find("location:") != std::string::npos)
                        {
                            getline(X, token,' ');
                            getline(X, token,' ');
                            location.set_path(token);
                            while(token.find("location:") != std::string::npos)
                            {
                                Location location;
                                while (getline())
                            }
                        }
                    }
                }
                servers.push_back(server);
            }
        }
    }
}