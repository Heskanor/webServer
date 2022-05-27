#include "configParser.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <vector>
#include "location.hpp"

//webserv config file parser
template< typename T >
ConfigParser<T>::ConfigParser()
{
    //hardcoded keyslist
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

template< typename T >
void ConfigParser<T>::strTabParser(std::string status,std::string line, T &lvl)
{
    std::string token;
    std::stringstream ss(line);
    while (getline(ss, token, ' '))
    {
        if (token.size() > 0)
        {
            (this->*t_directiveParser[status])(token,line,lvl);
        }
    }
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
                        action =1;
                    }
                }
                if (action == 0)
                {
                    std::cout << "Error: invalid key" << std::endl;
                    exit(1);
                }
            }
        }
        else if (token == "server:")
        {
            while (getline(ifs, line))
            {
                locationsCounter = 0;
                skipSpaces(line);
                std::stringstream Y(line);
                getline(Y, token,' ');
                else if (token == "location:")
                {
                    while (getline(ifs, line))
                    {
                        skipSpaces(line);
                        std::stringstream Y(line);
                        getline(Y, token,' ');
                        previousKey = token;
                        if (token == "server:")
                            break;
                        else if (token == "location:")
                            locationsCounter++;
                        else
                        {
                            for (int    j = 0; j < 13; j++)
                            {
                                if (token == (this->_keys)[j])
                                    (this->*t_directiveParser[j])(status, line, root._server(serverCounter)._location(locationsCounter));
                            }
                        }
                    }
                    locationsCounter++;
                }
                if (token == "server:")
                {
                    serverCounter++;
                    locationsCounter = 0;
                }
                else
                {
                    for (int    j = 0; j < 10; j++)
                    {
                        if (token == (this->_keys)[j])
                            (this->*t_directiveParser[j])(status, line, root._servers[serverCounter]);
                    }
                }   
            }
        }
    }
    return root;
}