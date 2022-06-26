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

	this->t_directiveParser.push_back(&ConfigParser::strTabParser);
    this->t_directiveParser.push_back(&ConfigParser::strTabParser);
    this->t_directiveParser.push_back(&ConfigParser::mapParser);
    this->t_directiveParser.push_back(&ConfigParser::intParser);
    this->t_directiveParser.push_back(&ConfigParser::intParser);
    this->t_directiveParser.push_back(&ConfigParser::strParser);
    this->t_directiveParser.push_back(&ConfigParser::strTabParser);
    this->t_directiveParser.push_back(&ConfigParser::strParser);
    this->t_directiveParser.push_back(&ConfigParser::strTabParser);
    this->t_directiveParser.push_back(&ConfigParser::strParser);
    this->t_directiveParser.push_back(&ConfigParser::strTabPortParser);
    this->t_directiveParser.push_back(&ConfigParser::strParser);
    this->t_directiveParser.push_back(&ConfigParser::strParser);

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
                                //std::cout << "Error: Auto-Index must be true or false" << std::endl;
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
                        //std::cout << "Error: BodySizeLimit must be a number" << std::endl;
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
                        //std::cout << "Error: Root must be a string" << std::endl;
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
                                //std::cout << "Error: Port must be a number" << std::endl;
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
                                //std::cout << "Error: Root must be a string" << std::endl;
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
                                        //std::cout << "Error: Auto-Index must be true or false" << std::endl;
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
                                //std::cout << "Error: Server Name must be a string" << std::endl;
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
                                //std::cout << "Error: BodySizeLimit must be a number" << std::endl;
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