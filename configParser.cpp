#include "configParser.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <vector>
#include "location.hpp"

//webserver config file parser
template< typename T >
ConfigParser<T>::ConfigParser()
{
    //hardcoded keys-list
	this->_keys[0] = "index:";//str table
	this->t_directiveParser.push_back(&ConfigParser::setIndex); //strTabParser);
	this->_keys[1] = "root:";//str
    this->t_directiveParser.push_back(&ConfigParser::setRoot);//strTabParser);
	this->_keys[2] = "errorPage:";//map
    this->t_directiveParser.push_back(&ConfigParser::setErrors);//mapParser);
	this->_keys[3] = "bodySizeLimit:";//int
    this->t_directiveParser.push_back(&ConfigParser::setBodySizeLimit);//intParser);;
    this->_keys[4] = "autoIndex:";//int
    this->t_directiveParser.push_back(&ConfigParser::setAutoIndex);//intParser);;
    this->_keys[5] = "uploadDirectory:";//str
    this->t_directiveParser.push_back(&ConfigParser::setUploadDirectory);//strParser);;
    this->_keys[6] = "allowedMethods:";//str table
    this->t_directiveParser.push_back(&ConfigParser::setAllowedMethods);//strTabParser);;
    this->_keys[7] = "serverName:";//str
    this->t_directiveParser.push_back(&ConfigParser::setServerName);//strParser);;
    this->_keys[8] = "listen:";//str port table
    this->t_directiveParser.push_back(&ConfigParser::setListen);//strTabPortParser);;
    this->_keys[9] = "redirection:";//str
    this->t_directiveParser.push_back(&ConfigParser::setRedirection);//strParser);;
    this->_keys[10] = "path:";//str
    this->t_directiveParser.push_back(&ConfigParser::setLocation);//strParser);;
    this->_keys[11] = "cgiPath:";//str
    this->t_directiveParser.push_back(&ConfigParser::setCgiPath);//strParser);;
    this->_keys[12] = "cgiExt:";//str table
    this->t_directiveParser.push_back(&ConfigParser::setCgiExt);//strTabParser);
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

template < typename T >
void ConfigParser<T>::intParser(std::string status,std::string line, T &root)
{
    int i = 0;
    skipFirstToken(line, status.length() - 1);
    if (line.find_first_not_of("0123456789") == std::string::npos)
        root = std::stoi(token);
    else
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
}

template< typename T >
void ConfigParser<T>::mapParser(std::string status,std::string line, T &root)
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
    if (find_first_not_of("0123456789") == std::string::npos)
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
    root.setErrorPage(token, value);
}

template< typename T >
void ConfigParser<T>::strParser(std::string status,std::string line, T &root)
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

template< typename T >
void ConfigParser<T>::strTabParser(std::string status,std::string line, T &lvl)
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
        lvl.push_back(token);
        i = j;
    }
}

template< typename T >
void ConfigParser<T>::setListen(std::string status,std::string line, T &lvl)
{
    //parse address:host 
    int j = 0;
    std::string token;
    skipFirstToken(line, status.length() - 1);
    while (line[j] != ':' && j< line.length())
        j++;
    token = line.substr(i, j-i);
    if (find_first_not_of("0123456789") == std::string::npos && token.length() =< 4)
            lvl._listenPort(std::stoi(token));
    else
    {
        lvl._listenAddress(token);
        if (line[j] == ' ')
        {
            std:cout << "error: listen address is not valid" << std::endl;
            exit(1);
        }
        else
        {
            while (line[j] != ' '&& line[j] != '\n' && j< line.length())
                j++;
            token = line.substr(i, j-i);
            // if token is not digit, error
            if (find_first_not_of("0123456789") == std::string::npos)
                lvl._listenPort(std::stoi(token));
            else
            {
                std::cout << "error: listen port is not valid" << std::endl;
                exit(1);
            }
        }
    }
}

template< typename T >
void ConfigParser<T>::setIndex(std::string token, std::string line, T &lvl)
{
    strTabParser(0, line, lvl.index);
}

template < typename T >
void ConfigParser<T>::setRoot(std::string status,std::string line, T &lvl)
{
    strParser(status, line, lvl.root);
}

template < typename T >
void ConfigParser<T>::setErrors(std::string status,std::string line, T &lvl)
{
    mapParser(status, line, lvl.errors);
}

template < typename T >
void ConfigParser<T>::setBodySizeLimit(std::string status,std::string line, T &lvl)
{
    intParser(status, line, lvl.bodySizeLimit);
    if (lvl.bodySizeLimit <= 0)
    {
        std::cout << "error: bodySizeLimit is not valid" << std::endl;
        exit(1);
    }
}

template < typename T >
void ConfigParser<T>::setAutoIndex(std::string status,std::string line, T &lvl)
{
    std::string s;
    strParser(status, line, s);
    if (s == "on" || s == "true")
        lvl.autoIndex = true;
    else if (s == "off" || s == "false")
        lvl.autoIndex = false;
    else
    {
        std::cout << "error: bad autoIndex value" << std::endl;
        exit(1);
    }
}
template < typename T >
void ConfigParser<T>::setUploadDirectory(std::string status,std::string line, T &lvl)
{
    strParser(status, line, lvl.uploadDirectory);
}

template < typename T >
void ConfigParser<T>::setAllowedMethods(std::string status,std::string line, T &lvl)
{
    strTabParser(status, line, lvl.allowedMethods);
}

template < typename T >
void ConfigParser<T>::setServerName(std::string status,std::string line, T &lvl)
{
    strParser(status, line, lvl.serverName);
}

template < typename T >
void ConfigParser<T>::setRedirection(std::string status,std::string line, T &lvl)
{
    mapParser(status, line, lvl.redirection);
}

template< typename T >
void ConfigParser<T>::setLocation(std::string status,std::string line, T &lvl)
{
    string s;
    strParser(status, line, s);
    lvl.push_back(s);
}

template< typename T >
void ConfigParser<T>::setLocation(std::string status,std::string line, T &lvl)
{
    string s;
    strParser(status, line, s);
    lvl.push_back(s);
}

template< typename T >
void ConfigParser<T>::setLocation(std::string status,std::string line, T &lvl)
{
    string s;
    strParser(status, line, s);
    lvl.push_back(s);
}
// void ConfigParser::strTabParser(std::string line, T &lvl)
// {
//     std::stringstream ss(line);
//     std::string token;
//     std::vector<std::string> strTab;
//     while (std::getline(ss, token, ' '))
//     {
//         strTab.push_back(token);
//     }
//     lvl.set_index(strTab);
// }

// bool isComment(std::string line)
// {
//     int i = 0;
//     while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
//         i++;
//     if (line[i] == '#')
//         return true;
//     return false;
// }

void skipSpaces(std::string &line)
{
    int i = 0;
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(0, i);
}
// i is the token length
void skipFirstToken(std::string &line,int i)
{
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(0, i);
}
template< typename T >
Root ConfigParser<T>::Rootparser(std::string file)
{
    std::ifstream ifs(file);
    std::string line;
    std::string status;
    std::string previousKey;
    std::string previousStatus;
    int action = 0;
    Server server = new Server();
    // Server server;
    size_t pos;
    std::string token;
    Root root;
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
                    if (token == (this->_keys)[j])
                    {
                        (this->*t_directiveParser[j])(status, line, root);
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
                else if (token == "location:" || previousStatus == "location:")
                {
                    Location location = new location();
                    while (getline(ifs, line) && line.find("}") == std::string::npos)
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
                            server.add_location(location);
                            Location location = new location();
                            continue;
                        }
                        else
                        {
                            for (int    j = 0; j < 13; j++)
                            {
                                if (token == (this->_keys)[j])
                                {
                                    (this->*t_directiveParser[j])(status, line, location);
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
                    previousStatus = status;
                    server.add_location(location);
                }
                
                else
                {
                    for (int j = 0; j < 10; j++)
                    {
                        if (token == (this->_keys)[j])
                        {
                            (this->*t_directiveParser[j])(status, line, root._servers[serverCounter]);
                            action = 1;
                        }    
                    }
                    if (action == 0)
                    {
                        std::cout << "Error: invalid server key" << std::endl;
                        exit(1);
                    }
                }
                if (line.find("}") == std::string::npos)
                {

                    root.add_server(server);
                    Server server = new Server();
                }   
            }
        }
    }
    return root;
}