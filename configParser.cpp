#include "configParser.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <vector>
#include <cstddef> 
#include <map>
#include "location.hpp"
#include "server.hpp"
#include "root.hpp"

//webserver config file parser

ConfigParser::ConfigParser()
{
    //hardcoded keys-list
	this->_rootkeys[0] = "index:";//str table
    this->_serverkeys[0] = "index:";//str table
    this->_locationkeys[0] = "index:";//str table
	this->t_rootParser.push_back(&ConfigParser::setIndex);
    this->t_serverParser.push_back(&ConfigParser::setIndex); //strTabParser);
	this->t_locationParser.push_back(&ConfigParser::setIndex);
    this->_rootkeys[1] = "root:";//str
    this->_serverkeys[1] = "root:";//str
    this->_locationkeys[1] = "root:";//str
    this->t_rootParser.push_back(&ConfigParser::setRoot);//strTabParser);
    this->t_serverParser.push_back(&ConfigParser::setRoot);
    this->t_locationParser.push_back(&ConfigParser::setRoot);
	this->_rootkeys[2] = "errorPage:";//map
    this->_serverkeys[2] = "errorPage:";//map
    this->_locationkeys[2] = "errorPage:";//map
    this->t_rootParser.push_back(&ConfigParser::setErrors);//mapParser);
	this->t_serverParser.push_back(&ConfigParser::setErrors);
    this->t_locationParser.push_back(&ConfigParser::setErrors);
    this->_rootkeys[3] = "bodySizeLimit:";//int
    this->_serverkeys[3] = "bodySizeLimit:";//int
    this->_locationkeys[3] = "bodySizeLimit:";//int
    this->t_rootParser.push_back(&ConfigParser::setBodySizeLimit);//intParser);
    this->t_serverParser.push_back(&ConfigParser::setBodySizeLimit);
    this->t_locationParser.push_back(&ConfigParser::setBodySizeLimit);
    this->_rootkeys[4] = "autoIndex:";//int
    this->_serverkeys[4] = "autoIndex:";//int
    this->_locationkeys[4] = "autoIndex:";//int
    this->t_rootParser.push_back(&ConfigParser::setAutoIndex);//intParser);;
    this->t_serverParser.push_back(&ConfigParser::setAutoIndex);
    this->t_locationParser.push_back(&ConfigParser::setAutoIndex);
    this->_rootkeys[5] = "uploadDirectory:";//str
    this->_serverkeys[5] = "uploadDirectory:";//str
    this->_locationkeys[5] = "uploadDirectory:";//str
    this->t_rootParser.push_back(&ConfigParser::setUploadDirectory);//strParser);
    this->t_serverParser.push_back(&ConfigParser::setUploadDirectory);//strParser);
    this->t_locationParser.push_back(&ConfigParser::setUploadDirectory);//strParser);
    this->_rootkeys[6] = "allowedMethods:";//str table
    this->_serverkeys[6] = "allowedMethods:";//str table
    this->_locationkeys[6] = "allowedMethods:";//str table
    this->t_rootParser.push_back(&ConfigParser::setAllowedMethods);//strTabParser);
    this->t_serverParser.push_back(&ConfigParser::setAllowedMethods);//strTabParser);
    this->t_locationParser.push_back(&ConfigParser::setAllowedMethods);//strTabParser);
    this->_serverkeys[7] = "serverName:";//str
    this->t_serverParser.push_back(&ConfigParser::setServerName);//strParser);;
    this->_serverkeys[8] = "listen:";//str port table
    this->t_serverParser.push_back(&ConfigParser::setListen);//strTabPortParser);
    this->_locationkeys[7] = "redirection:";//str
    this->t_locationParser.push_back(&ConfigParser::setRedirection);//strParser);
    this->_locationkeys[8] = "path:";//str
    this->t_locationParser.push_back(&ConfigParser::setLocation);//strParser);
    this->_locationkeys[9] = "cgiPath:";//str
    this->t_locationParser.push_back(&ConfigParser::setCgiPath);//strParser);
    this->_locationkeys[10] = "cgiExt:";//str table
    this->t_locationParser.push_back(&ConfigParser::setCgiExt);//strTabParser);
}
ConfigParser::~ConfigParser()
{
}
void skipSpaces(std::string &line)
{
    int i = 0;
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(0, i);
}

void skipFirstToken(std::string &line,int i)
{
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(0, i);
}
//issue: with this function: i need to extract token before converting it to int
void ConfigParser::intParser(std::string status,std::string line, int &size)
{
    int i = 0;
    skipFirstToken(line, status.length() - 1);
    if (line.find_first_not_of("0123456789") == std::string::npos)
        size = std::stoi(line);
    else
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
}

void ConfigParser::strParser(std::string status,std::string line, std::string &root)
{
    std::string token;
    skipFirstToken(line, status.length() - 1);
    int i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    root = token;
}

void ConfigParser::strTabParser(std::string status,std::string line, std::vector<std::string> &str)
{
    //push tokens into lvl vector
    std::string token;
    int i = 0;
    skipFirstToken(line, status.length() - 1);
    while (line[i] != '\n')
    {
        while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
            i++;
        int j = i;
        while (line[j] != ' ' && j< line.length())
            j++;
        token = line.substr(i, j-i);
        str.push_back(token);
        i = j;
    }
}

void ConfigParser::setRedirection(std::string status,std::string line, Location &root)
{
    std::string token;
    std::string value;
    int val;
    int i = 0;
    skipFirstToken(line, status.length() - 1);
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    if (token.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
    skipSpaces(line);
    i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        value += line[i];
        i++;
    }
    root.add_redirect_map(token, value);
}

void ConfigParser::setIndex(std::string token, std::string line, Root &lvl)
{
    std::vector<std::string> ind;
    strTabParser(0, line, ind);
    lvl.set_index(ind);
}
void ConfigParser::setIndex(std::string token, std::string line, Server &lvl)
{
    std::vector<std::string> ind;
    strTabParser(0, line, ind);
    lvl.set_index(ind);
}
void ConfigParser::setIndex(std::string token, std::string line, Location &lvl)
{
    std::vector<std::string> ind;
    strTabParser(0, line, ind);
    lvl.set_index(ind);
}

void ConfigParser::setErrors(std::string status,std::string line, Root &root)
{
    std::string token;
    std::string value;
    int val;
    int i = 0;
    skipFirstToken(line, status.length() - 1);
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    if (token.find_first_not_of("0123456789") == std::string::npos)
        val = std::stoi(token);
    else
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
    skipSpaces(line);
    i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        value += line[i];
        i++;
    }
    root.add_error_map(token, value);
}
void ConfigParser::setErrors(std::string status,std::string line, Server &root)
{
    std::string token;
    std::string value;
    int val;
    int i = 0;
    skipFirstToken(line, status.length() - 1);
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    if (token.find_first_not_of("0123456789") == std::string::npos)
        val = std::stoi(token);
    else
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
    skipSpaces(line);
    i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        value += line[i];
        i++;
    }
    root.add_error_map(token, value);
}
void ConfigParser::setErrors(std::string status,std::string line, Location &root)
{
    std::string token;
    std::string value;
    int val;
    int i = 0;
    skipFirstToken(line, status.length() - 1);
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    if (token.find_first_not_of("0123456789") == std::string::npos)
        val = std::stoi(token);
    else
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
    skipSpaces(line);
    i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        value += line[i];
        i++;
    }
    root.add_error_map(token, value);
}

void ConfigParser::setListen(std::string status,std::string line, Server &lvl)
{
    //parse address:host 
    int j = 0;
    std::string token;
    skipFirstToken(line, status.length() - 1);
    int i =0;
    while (line[j] != ':' && j< line.length())
        j++;
    token = line.substr(i, j-i);
    if (token.find_first_not_of("0123456789") == std::string::npos && token.length() <= 4)
            lvl.set_listenPort(token);
    else
    {
        lvl.set_listenAddress(token);
        if (line[j] == ' ')
        {
            std::cout << "error: listen address is not valid" << std::endl;
            exit(1);
        }
        else
        {
            while (line[j] != ' '&& line[j] != '\n' && j< line.length())
                j++;
            token = line.substr(i, j-i);
            // if token is not digit, error
            if (token.find_first_not_of("0123456789") == std::string::npos)
                lvl.set_listenPort(token);
            else
            {
                std::cout << "error: listen port is not valid" << std::endl;
                exit(1);
            }
        }
    }
}

void ConfigParser::setRoot(std::string status,std::string line, Root &lvl)
{
    std::string tko;
    strParser(status, line, tko);
    lvl.set_root(tko);
}
void ConfigParser::setRoot(std::string status,std::string line, Server &lvl)
{
    std::string tko;
    strParser(status, line, tko);
    lvl.set_root(tko);
}
void ConfigParser::setRoot(std::string status,std::string line, Location &lvl)
{
    std::string tko;
    strParser(status, line, tko);
    lvl.set_root(tko);
}

void ConfigParser::setBodySizeLimit(std::string status,std::string line, Root &lvl)
{
    int size;
    intParser(status, line, size);
    if (size <= 0)
    {
        std::cout << "error: bodySizeLimit is not valid" << std::endl;
        exit(1);
    }
    lvl.set_bodySizeLimit(size);
}
void ConfigParser::setBodySizeLimit(std::string status,std::string line, Server &lvl)
{
    int size;
    intParser(status, line, size);
    if (size <= 0)
    {
        std::cout << "error: bodySizeLimit is not valid" << std::endl;
        exit(1);
    }
    lvl.set_bodySizeLimit(size);
}
void ConfigParser::setBodySizeLimit(std::string status,std::string line, Location &lvl)
{
    int size;
    intParser(status, line, size);
    if (size <= 0)
    {
        std::cout << "error: bodySizeLimit is not valid" << std::endl;
        exit(1);
    }
    lvl.set_bodySizeLimit(size);
}

void ConfigParser::setAutoIndex(std::string status,std::string line, Root &lvl)
{
    std::string s;
    strParser(status, line, s);
    if (s == "on" || s == "true")
        lvl.set_auto_index(true);
    else if (s == "off" || s == "false")
        lvl.set_auto_index(false);
    else
    {
        std::cout << "error: bad autoIndex value" << std::endl;
        exit(1);
    }
}
void ConfigParser::setAutoIndex(std::string status,std::string line, Server &lvl)
{
    std::string s;
    strParser(status, line, s);
    if (s == "on" || s == "true")
        lvl.set_auto_index(true);
    else if (s == "off" || s == "false")
        lvl.set_auto_index(false);
    else
    {
        std::cout << "error: bad autoIndex value" << std::endl;
        exit(1);
    }
}
void ConfigParser::setAutoIndex(std::string status,std::string line, Location &lvl)
{
    std::string s;
    strParser(status, line, s);
    if (s == "on" || s == "true")
        lvl.set_auto_index(true);
    else if (s == "off" || s == "false")
        lvl.set_auto_index(false);
    else
    {
        std::cout << "error: bad autoIndex value" << std::endl;
        exit(1);
    }
}

void ConfigParser::setUploadDirectory(std::string status,std::string line, Root &lvl)
{
    std::string s;
    strParser(status, line, s);
    lvl.set_upload_directory(s);
}
void ConfigParser::setUploadDirectory(std::string status,std::string line, Server &lvl)
{
    std::string s;
    strParser(status, line, s);
    lvl.set_upload_directory(s);
}
void ConfigParser::setUploadDirectory(std::string status,std::string line, Location &lvl)
{
    std::string s;
    strParser(status, line, s);
    lvl.set_upload_directory(s);
}

void ConfigParser::setAllowedMethods(std::string status,std::string line, Root &lvl)
{
    std::vector<std::string> meth;
    strTabParser(status, line, meth);
    lvl.set_allowed_methods(meth);
}
void ConfigParser::setAllowedMethods(std::string status,std::string line, Server &lvl)
{
    std::vector<std::string> meth;
    strTabParser(status, line, meth);
    lvl.set_allowed_methods(meth);
}
void ConfigParser::setAllowedMethods(std::string status,std::string line, Location &lvl)
{
    std::vector<std::string> meth;
    strTabParser(status, line, meth);
    lvl.set_allowed_methods(meth);
}

void ConfigParser::setServerName(std::string status,std::string line, Server &lvl)
{
    std::string s;
    strParser(status, line, s);
    lvl.set_server_name(s);
}

void ConfigParser::setLocation(std::string status,std::string line, Location &lvl)
{
    std::string s;
    strParser(status, line, s);
    lvl.set_path(s);
}

void ConfigParser::setCgiPath(std::string status,std::string line, Location &root)
{
    std::string s;
    strParser(status, line, s);
    root.set_cgi_path(s);
}

void ConfigParser::setCgiExt(std::string status,std::string line, Location &root)
{
    std::vector<std::string> s;
    strTabParser(status, line, s);
    root.set_cgi_ext(s);
}

Root *ConfigParser::Rootparser(std::string file)
{
    std::ifstream ifs(file);
    std::string line;
    std::string status;
    std::string previousKey;
    std::string previousStatus;
    int action = 0;
    Root *root = new Root();
    Server *server = new Server();
    // Server server;
    size_t pos;
    std::string token;
    int serverCounter = 0;
    int locationsCounter = 0;
    int i;
    if (ifs.is_open())
    {
        getline(ifs, line);
        skipSpaces(line);
        std::stringstream X(line);
        getline(X, token,' ');
        if (token != "server:")
        {
            while (getline(ifs, line))
            {
                action = 0;
                skipSpaces(line);
                std::stringstream Y(line);
                getline(Y, token,' ');
                previousKey = token;
                if (token == "server:")
                    break;
                for (int    j = 0; j < 7; j++)
                {
                    if (token == (this->_rootkeys)[j])
                    {
                        (this->*t_rootParser[j])(status, line, *root);
                        action = 1;
                    }
                }
                if (action == 0)
                {
                    std::cout << "Error: invalid key" << std::endl;
                    exit(1);
                }
            }
        }
        else
        {
            while (getline(ifs, line))
            {
                action = 0;
                locationsCounter = 0;
                skipSpaces(line);
                std::stringstream Y(line);
                getline(Y, token,' ');
                if (token == "location:")
                {
                    Location *location = new Location();
                    while (getline(ifs, line))
                    {
                        action = 0;
                        skipSpaces(line);
                        std::stringstream Y(line);
                        getline(Y, token,' ');
                        previousKey = token;
                        if (token == "server:")
                        {
                            status = token;
                            break;
                        }
                        if (token == "location:")
                        {
                            server->add_location(*location);
                            Location *location = new Location();
                            continue;
                        }
                        else
                        {
                            for (int    j = 0; j < 10; j++)
                            {
                                if (token == (this->_locationkeys)[j])
                                {
                                    (this->*t_locationParser[j])(token, line, *location);
                                    action = 1;
                                }
                            }
                        }
                        if (action == 0)
                        {
                            std::cout << "Error: invalid key" << std::endl;
                            exit(1);
                        }
                    }
                    server->add_location(*location);
                }
                else if(token == "server:")
                {
                    root->add_server(*server);
                    Root* server = new Server();
                }
                else
                {
                    for (int j = 0; j < 10; j++)
                    {
                        if (token == (this->_serverkeys)[j])
                        {
                            (this->*t_serverParser[j])(token, line, *server);
                            action = 1;
                        }    
                    }
                    if (action == 0)
                    {
                        std::cout << "Error: invalid server key" << std::endl;
                        exit(1);
                    }
                }
            }
            root->add_server(*server);
        }
    }
    return root;
}