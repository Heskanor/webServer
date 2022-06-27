#include <iostream>
#include <fstream>
#include <sstream> 
#include <cstddef> 
#include <string>
#include <vector>
#include <map>
#include "configParser.hpp"
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
    this->_serverkeys[9] = "return:";//str
    this->_locationkeys[7] = "return:";//str
    this->t_serverParser.push_back(&ConfigParser::setRedirection);//strParser);
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
    unsigned int i = 0;
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(0, i);
}

void skipFirstToken(std::string &line,unsigned int i)
{
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(line.begin(), line.begin() +i);
}

void ConfigParser::intParser(std::string status,std::string line, int &size)
{
    skipFirstToken(line, status.length());
    if (line.find_first_not_of("0123456789") == std::string::npos)
    {
        std::stringstream ss;
        ss << line;
        ss >> size;
        
        // size = std::stoi(line);
    }    
    else
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
}
void longParser(std::string status,std::string line, long long &size)
{
    skipFirstToken(line, status.length());
    if (line.find_first_not_of("0123456789") == std::string::npos)
    {
        std::stringstream ss;
        ss << line;
        ss >> size;
        
        // size = std::stoi(line);
    }    
    else
    {
        std::cout << "error: bad error Code" << std::endl;
        exit(1);
    }
}

void ConfigParser::strParser(std::string status,std::string line, std::string &root)
{
    std::string token;

    skipFirstToken(line, status.length());
    unsigned int i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    root = token;
}

void ConfigParser::strTabParser(std::string status,std::string line, std::vector<std::string> &str)
{
    std::string token;
    unsigned int i = 0;
    
    skipFirstToken(line, status.length());
    while (line[i] != '\n' &&  i <line.length())
    {
        while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
            i++;
        unsigned int j = i;
        while (line[j] != ' ' && j< line.length())
            j++;
        token = line.substr(i, j-i);
        str.push_back(token);
        i = j;
    }
}
// I get to check the case where we can have the redirection path alone
void ConfigParser::setRedirection(std::string status,std::string line, Location &root)
{
    // std::string token;
    // std::string value;
    // std::string val;
    // unsigned int i = 0;

    // skipFirstToken(line, status.length());
    // while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    // {
    //     token += line[i];
    //     i++;
    // }
    // if (token.find_first_not_of("0123456789") == std::string::npos && token.length() == 3 && token >= "300" && token <= "599")
    //     val = token;
    // else
    // {
    //     std::cout << "Redirection code " << token << " must be between 300 and 599" << std::endl;
    //     exit(1);
    // }
    // line.erase(0,i);
    // skipSpaces(line);
    // i = 0;
    // while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    // {
    //     value += line[i];
    //     i++;
    // }
    // root.set_redirection(val, value);
    std::string tko;
    strParser(status, line, tko);
    root.set_redirection(tko, tko);
}

void ConfigParser::setRedirection(std::string status,std::string line, Server &root)
{
    // std::string token;
    // std::string value;
    // std::string val;
    // unsigned int i = 0;

    // skipFirstToken(line, status.length());
    // while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    // {
    //     token += line[i];
    //     i++;
    // }
    // if (token.find_first_not_of("0123456789") == std::string::npos && token.length() == 3 && token >= "300" && token <= "599")
    //     val = token;
    // else
    // {
    //     std::cout << "Redirection code " << token << " must be between 300 and 599" << std::endl;
    //     exit(1);
    // }
    // line.erase(0,i);
    // skipSpaces(line);
    // i = 0;
    // while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    // {
    //     value += line[i];
    //     i++;
    // }
    std::string tko;
    strParser(status, line, tko);
    root.set_redirection(tko, tko);
}

void ConfigParser::setIndex(std::string token, std::string line, Root &lvl)
{
    std::vector<std::string> ind;
    strTabParser(token, line, ind);
    lvl.set_index(ind);
}
void ConfigParser::setIndex(std::string token, std::string line, Server &lvl)
{
    std::vector<std::string> ind;
    strTabParser(token, line, ind);
    lvl.set_index(ind);
}
void ConfigParser::setIndex(std::string token, std::string line, Location &lvl)
{
    std::vector<std::string> ind;
    strTabParser(token, line, ind);
    lvl.set_index(ind);
}

void ConfigParser::setErrors(std::string status,std::string line, Root &root)
{
    std::string token;
    std::string value;
    std::string val;
    unsigned int i = 0;
    skipFirstToken(line, status.length());
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    if (token.find_first_not_of("0123456789") == std::string::npos && token.length() == 3 && token >= "300" && token <= "599")
        val = token;
    else
    {
        std::cout << "Error code " << token << " must be between 300 and 599" << std::endl;
        exit(1);
    }
    line.erase(0,i);
    skipSpaces(line);
    i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        value += line[i];
        i++;
    }
    root.add_error_map(val, value);
}
void ConfigParser::setErrors(std::string status,std::string line, Server &root)
{
    std::string token;
    std::string value;
    std::string val;
    unsigned int i = 0;
    skipFirstToken(line, status.length());
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    if (token.find_first_not_of("0123456789") == std::string::npos && token.length() == 3 && token >= "300" && token <= "599")
        val = token;
    else
    {
        std::cout << "Error code " << token << " must be between 300 and 599" << std::endl;
        exit(1);
    }
    line.erase(0,i);
    skipSpaces(line);
    i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        value += line[i];
        i++;
    }
    root.add_error_map(val, value);
}
void ConfigParser::setErrors(std::string status,std::string line, Location &root)
{
    std::string token;
    std::string value;
    std::string val;
    unsigned int i = 0;
    skipFirstToken(line, status.length());
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        token += line[i];
        i++;
    }
    if (token.find_first_not_of("0123456789") == std::string::npos && token.length() == 3 && token >= "300" && token <= "599")
        val = token;
    else
    {
        std::cout << "Error code " << token << " must be between 300 and 599" << std::endl;
        exit(1);
    }
    line.erase(0,i);
    skipSpaces(line);
    i = 0;
    while (line[i] != ' '&& line[i]!= '\n' && i < line.length())
    {
        value += line[i];
        i++;
    }
    root.add_error_map(val, value);
}

void ConfigParser::setListen(std::string token,std::string line, Server &lvl)
{
    //parse address:host 
    unsigned int j = 0;

    skipFirstToken(line, token.length());
    while (line[j] != ':' && j< line.length())
        j++;
    //if (j <line.length())
        //token = line.substr(0, j);
    if (j >= line.length() && token.find_first_not_of("0123456789") == std::string::npos && token.length() <= 4)
            lvl.set_listenPort(token);
    else
    {
        
        if (line[j] == ' ')
        {
            std::cout << "error: listen address is not valid" << std::endl;
            exit(1);
        }
        else
        {
            token = line.substr(0, j);
            lvl.set_listenAddress(token);
            while ((line[j] == ' '|| line[j] == '\n' || line[j] == ':' )&& j< line.length())
                j++;
            token = line.substr(j, line.length());
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
    long long size;
    longParser(status, line, size);
    if (size <= 0)
    {
        std::cout << "error: bodySizeLimit is not valid" << std::endl;
        exit(1);
    }
    lvl.set_bodySizeLimit(size);
}
void ConfigParser::setBodySizeLimit(std::string status,std::string line, Server &lvl)
{
    long long size;
    longParser(status, line, size);
    if (size <= 0)
    {
        std::cout << "error: bodySizeLimit is not valid" << std::endl;
        exit(1);
    }
    lvl.set_bodySizeLimit(size);
}
void ConfigParser::setBodySizeLimit(std::string status,std::string line, Location &lvl)
{
    long long size;
    longParser(status, line, size);
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
    std::vector<std::string>::iterator it;
    for (it = meth.begin(); it != meth.end(); it++)
    {
        if (*it == "GET" || *it == "POST" || *it == "DELETE")
            lvl.add_allowed_method(*it);
        else
        {
            std::cout << "error: bad allowedMethod value" << std::endl;
            exit(1);
        }
    }
}
void ConfigParser::setAllowedMethods(std::string status,std::string line, Server &lvl)
{
    std::vector<std::string> meth;
    strTabParser(status, line, meth);
    std::vector<std::string>::iterator it;
    for (it = meth.begin(); it != meth.end(); it++)
    {
        if (*it == "GET" || *it == "POST" || *it == "DELETE")
            lvl.add_allowed_method(*it);
        else
        {
            std::cout << "error: bad allowedMethod value" << std::endl;
            exit(1);
        }
    }
}
void ConfigParser::setAllowedMethods(std::string status,std::string line, Location &lvl)
{
    std::vector<std::string> meth;
    strTabParser(status, line, meth);
    std::vector<std::string>::iterator it;
    for (it = meth.begin(); it != meth.end(); it++)
    {
        if (*it == "GET" || *it == "POST" || *it == "DELETE")
            lvl.add_allowed_method(*it);
        else
        {
            std::cout << "error: bad allowedMethod value" << std::endl;
            exit(1);
        }
    }
}

void ConfigParser::setServerName(std::string status,std::string line, Server &lvl)
{
    std::vector<std::string> s;
    strTabParser(status, line, s);
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

void ConfigParser::root_checker(Root root)
{
    std::vector<Server> s = root.get_servers();
    std::vector<std::string> str;
    
    if (s.empty())
    {
        std::cout << "Error : you have to set a server";
        exit(1);
    }
    else
    {
        for (std::vector<Server>::iterator it = s.begin(); it != s.end(); ++it)
        {
            if (it->check_empty())
            {
                std::cout << "Error : Missing server directive or location";
                exit(1);
            }
            else
            {
                std::vector<Location> locations = it->get_locations();
                for (std::vector<Location>::iterator it2 = locations.begin(); it2 != locations.end(); ++it2)
                {
                    if (it2->check_lempty())
                    {
                        std::cout << "Error : Missing location directive";
                        exit(1);
                    }
                }
            }
        }
    }
}

Root ConfigParser::Rootparser(std::string file)
{
    std::ifstream ifs(file);
    std::string line;
    int action = 0;
    Root root;
    Location location;
    Server server;
    std::string token;
    std::map<std::string, int> rootAdminer;
    std::map<std::string, int> serverAdminer;
    std::map<std::string, int> locationAdminer;
    Location defaultLocation;
    if (ifs.is_open())
    {
        getline(ifs, line);
        skipSpaces(line);
        std::stringstream X(line);
        getline(X, token,' ');
        if (token != "server:")
        {
            for (int    j = 0; j < 7; j++)
            {
                if (token == (this->_rootkeys)[j])
                {
                    (this->*t_rootParser[j])(token, line, root);
                    action = 1;
                }
            }
            if (action == 0)
            {
                std::cout << "Error: invalid key" << std::endl;
                exit(1);
            }
            while (getline(ifs, line))
            {
                action = 0;
                skipSpaces(line);
                std::stringstream Y(line);
                getline(Y, token,' ');
                if (token == "server:")
                    break;
                for (int    j = 0; j < 7; j++)
                {
                    if (token == (this->_rootkeys)[j])
                    {
                        if (rootAdminer.find(token) != rootAdminer.end() && token != "errorPage:"&& token != "path:")
                        {
                            std::cout << "Error: repeated directive" << std::endl;
                            exit(1);
                        }
                        rootAdminer[token] = 1;
                        (this->*t_rootParser[j])(token, line, root);
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
        while (getline(ifs, line))
        {
            action = 0;
            skipSpaces(line);
            std::stringstream Y(line);
            getline(Y, token,' ');
            if (token == "location:")
            {
                location.clear(server);
                locationAdminer.clear();
                while (getline(ifs, line))
                {
                    action = 0;
                    skipSpaces(line);
                    std::stringstream Y(line);
                    getline(Y, token,' ');
                    if (token == "server:")
                    {
                        server.add_location(location);
                        

						defaultLocation.clear(server);
						server.insert_location(defaultLocation);
                        root.add_server(server);
                        serverAdminer.clear();
                        locationAdminer.clear();
                        location.clear(server);
                        server.clear(root);
                        action = -1;
                        break;
                    }
                    else if (token == "location:")
                    {
                        server.add_location(location);
                         locationAdminer.clear();
                        location.clear(server);
                        action = 7;
                        continue;
                    }
                    else
                    {
                        for (int    j = 0; j < 11; j++)
                        {
                            if (token == (this->_locationkeys)[j])
                            {
                                if (locationAdminer.find(token) != locationAdminer.end() && token != "errorPage:")
                                {
                                    std::cout << "Error: repeated directive["<< token<<"]" << std::endl;
                                    exit(1);
                                }
                                locationAdminer[token] = 1;
                                (this->*t_locationParser[j])(token, line, location);
                                action = 1;
                            }
                        }
                    }
                    if (action == 0)
                    {
                        std::cout << "Error: invalid location key near :" << token<<std::endl;
                        exit(1);
                    }
                }
                if (action != -1 && action != 7)
                {
                    server.add_location(location);
                     locationAdminer.clear();
                }
                location.clear(server);
            }
            else if(token == "server:")
            {
				defaultLocation.clear(server);
				server.insert_location(defaultLocation);
                root.add_server(server);
                locationAdminer.clear();
                serverAdminer.clear();
                server.clear(root);
            }
            else
            {
                for (int j = 0; j < 9; j++)
                {
                    if (token == (this->_serverkeys)[j])
                    {
                        if (serverAdminer.find(token) != serverAdminer.end() && token != "errorPage:")
                        {
                            std::cout << "Error: repeated directive" << std::endl;
                            exit(1);
                        }
                        serverAdminer[token] = 1;
                        (this->*t_serverParser[j])(token, line, server);
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
        std::vector<Server> s = root.get_servers();
        for (std::vector<Server>::iterator it = s.begin(); it != s.end(); ++it)
        {
            if (it->get_server_name() == server.get_server_name()&& it->get_listenAddress() == server.get_listenAddress() && it->get_listenPort() == server.get_listenPort())
            {
                std::cout << "Error: duplicated server" << std::endl;
                exit(1);
            }
        }
		defaultLocation.clear(server);
		server.insert_location(defaultLocation);
        root.add_server(server);
        serverAdminer.clear();
        server.clear(root);
    }
    serverAdminer.clear();
    root_checker(root);
    return root;
}