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
	this->_keys[2] = "errors:";//map
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
void ConfigParser<T>::strTabParser(std::string line, T &lvl)
{
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> strTab;
    while (std::getline(ss, token, ' '))
    {
        strTab.push_back(token);
    }
    lvl.set_index(strTab);
}

bool isComment(std::string line)
{
    int i = 0;
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    if (line[i] == '#')
        return true;
    return false;
}

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
        //skip empty spaces
        skipSpaces(line);
        //-----------------------------------------------------
        // is root?
        std::stringstream X(line);
        getline(X, token,' ');
        //-----------------------------------------------------
        // is root?
        if (token == "root:")
        {
            status = "root:";
            //look for comments
            i = 5;
            while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
                i++;
            if (line[i] && line[i] != '#')
            {
                std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
                exit(1);
            }
            //-----------------------------------------------------
            std::cout << "|"<< "Good start sir :)" << "|"<<std::endl;
            while (getline(ifs, line))
            {
                if (!isComment(line))
                {
                    //skip empty spaces
                    skipSpaces(line);
                    std::stringstream Y(line);
                    getline(Y, token,' ');
                    previousKey = token;
                    if (token == "server:" && status == "server:")
                        serverCounter++;
                    if (status == "root:" && token != "server:")
                    {
                        for (int    j = 0; j < 7; j++)
                        {
                            if (token == (this->_keys)[j])
                                (this->*t_directiveParser[j])(status, line, root);
                        }
                    }else if (token == "server:")
                    {
                        previousKey = token;
                        getline(ifs, line);
                        skipSpaces(line);
                        std::stringstream Y(line);
                        getline(Y, token,' ');
                        status = "server:";
                        for (int    j = 0; j < 10; j++)
                        {
                            if (token == (this->_keys)[j])
                                (this->*t_directiveParser[j])(status, line, root._servers[serverCounter]);
                        }
                        if (token == "location:")
                        {
                            status = "location:";
                            token = "lol";
                            while (getline(ifs, line) && (token != "server:") && (token != "location:"))
                            {
                                if (!isComment(line))
                                {
                                    //skip empty spaces
                                    skipSpaces(line);
                                    std::stringstream Z(line);
                                    getline(Z, token,' ');
                                    previousStatus = token;
                                    if (token != "location:" && token != "server:")
                                    {
                                        for (int    j = 0; j < 13; j++)
                                        {
                                            if (token == (this->_keys)[j])
                                                (this->*t_directiveParser[j])(status, line, root._servers[serverCounter]._locations[locationCounter]);
                                        }
                                    }
                                }
                            }
                            // location can skip a server by mistake
                            locationsCounter++;
                        }
                    }
                }
            }
        }
    }
    return root;
}