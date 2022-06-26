#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

#include <iostream>
#include <stack>
#include <list>
#include "server.hpp"
#include "location.hpp"
#include "root.hpp"


class ConfigParser
{
    public:
        // screw template <typedef T>
        typedef void (ConfigParser::*rootParser)(std::string token,std::string line, Root &lvl);
        typedef void (ConfigParser::*serverParser)(std::string token,std::string line, Server &lvl);
        typedef void (ConfigParser::*locationParser)(std::string token,std::string line, Location &lvl);
        std::string _rootkeys[7];
        std::string _serverkeys[11];
        std::string _locationkeys[12];
        std::vector<rootParser> t_rootParser;
        std::vector<serverParser> t_serverParser;
        std::vector<locationParser> t_locationParser;
        ConfigParser();
        ConfigParser(const ConfigParser &src);
        ~ConfigParser();
        ConfigParser &operator=( ConfigParser const & rhs );
        Root Rootparser(std::string file);
        void root_checker(Root root);
    private:
        void strTabParser(std::string status,std::string line, std::vector<std::string> &str);
        void strParser(std::string status,std::string line, std::string &root);
        void intParser(std::string status,std::string line, int &size);
        void setIndex(std::string status,std::string line, Root &root);
        void setRoot(std::string status,std::string line, Root &root);
        void setErrors(std::string status,std::string line, Root &root);
        void setBodySizeLimit(std::string status,std::string line, Root &root);
        void setAutoIndex(std::string status,std::string line, Root &root);
        void setUploadDirectory(std::string status,std::string line, Root &root);
        void setAllowedMethods(std::string status,std::string line, Root &root);

        void setIndex(std::string status,std::string line, Server &root);
        void setRoot(std::string status,std::string line, Server &root);
        void setErrors(std::string status,std::string line, Server &root);
        void setBodySizeLimit(std::string status,std::string line, Server &root);
        void setAutoIndex(std::string status,std::string line, Server &root);
        void setUploadDirectory(std::string status,std::string line, Server &root);
        void setAllowedMethods(std::string status,std::string line, Server &root);
        void setServerName(std::string status,std::string line, Server &root);
        void setListen(std::string status,std::string line, Server &root);
        void setRedirection(std::string status,std::string line, Server &root);
     
        void setIndex(std::string status,std::string line, Location &root);
        void setRoot(std::string status,std::string line, Location &root);
        void setErrors(std::string status,std::string line, Location &root);
        void setBodySizeLimit(std::string status,std::string line, Location &root);
        void setAutoIndex(std::string status,std::string line, Location &root);
        void setUploadDirectory(std::string status,std::string line, Location &root);
        void setAllowedMethods(std::string status,std::string line, Location &root);
        void setRedirection(std::string status,std::string line, Location &root);
        void setLocation(std::string status,std::string line, Location &root);
        void setCgiPath(std::string status,std::string line, Location &root);
        void setCgiExt(std::string status,std::string line, Location &root);
};

#endif