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
    //hardcoded keyslist
	this->_keys[0] = "index:";//str table
	this->t_directiveParser.push_back(&ConfigParser::setIndex); //strTabParser);
	this->_keys[1] = "root:";//str
    this->t_directiveParser.push_back(&ConfigParser::setRoot);//strTabParser);
	this->_keys[2] = "errors:";//map
    this->t_directiveParser.push_back(&ConfigParser::setErrors);//mapParser);
	this->_keys[3] = "bodySizeLimit:";//int
    this->t_directiveParser.push_back(&ConfigParser::setBodySizeLimit//intParser);
    this->_keys[4] = "autoIndex:";//int
    this->t_directiveParser.push_back(&ConfigParser::setAutoIndex//intParser);
    this->_keys[5] = "uploadDirectory:";//str
    this->t_directiveParser.push_back(&ConfigParser::setUploadDirectory//strParser);
    this->_keys[6] = "allowedMethods:";//str table
    this->t_directiveParser.push_back(&ConfigParser::setAllowedMethods//strTabParser);
    this->_keys[9] = "serverName:";//str
    this->t_directiveParser.push_back(&ConfigParser::setServerName//strParser);
    this->_keys[10] = "listen:";//str port table
    this->t_directiveParser.push_back(&ConfigParser::setListen//strTabPortParser);
    this->_keys[12] = "redirection:";//str
    this->t_directiveParser.push_back(&ConfigParser::setRedirection//strParser);
    this->_keys[11] = "locations:";//str
    this->t_directiveParser.push_back(&ConfigParser::setLocation//strParser);
    this->_keys[7] = "cgiPath:";//str
    this->t_directiveParser.push_back(&ConfigParser::setCgiPath//strParser);
    this->_keys[8] = "cgiExt:";//str table
    this->t_directiveParser.push_back(&ConfigParser::setCgiExt//strTabParser);
}

void ConfigParser::strTabParser(std::string line, Root &root)
{
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> strTab;
    while (std::getline(ss, token, ' '))
    {
        strTab.push_back(token);
    }
    root.set_index(strTab);
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

Root ConfigParser::Rootparser(std::string file)
{
    std::ifstream ifs("Configfile");
    std::string line;
    std::string status;
    std::string previousKey;
    size_t pos;
    std::string token;
    Root root;
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
        if (token == "root:")
        {   status = "root:";
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
                    //-----------------------------------------------------
                    // is root?
                    std::stringstream Y(line);
                    getline(Y, token,' ');
                    previousKey = token;
                    if (previousKey == "server:")
                        status = "server:";
                    if (status == "root:")
                    {
                        for (int    j = 0; j < 7; j++)
                        {
                            if (token == (this->_keys)[j])
                                (this->*t_directiveParser[j])(line, root);
                        }
                    }
                    else if (status =="server:")
                    {
                        //look for comments
                        i = 7;
                        while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
                            i++;
                        if (line[i] && line[i] != '#')
                        {
                            std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
                            exit(1);
                        }
                        /* code */
                    }else
                    {
                        std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
                        exit(1);
                    }
                }
            }
        }
        else
        {
            std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
            exit(1);
        }
    }
    return 0;
}