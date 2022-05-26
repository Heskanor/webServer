#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

#include <iostream>
#include <stack>
#include <list>
#include "server.hpp"
#include "location.hpp"
#include "root.hpp"

template < typename T >
class ConfigParser
{
    public:
        std::string _keys[12];
        
        typedef void (ConfigParser::*directiveParser)(std::string token,std::string line, T &lvl);
        std::vector<directiveParser> t_directiveParser;
        ConfigParser() {}
        ConfigParser(const ConfigParser &src){}
        ~ConfigParser() {}
        ConfigParser &operator=( ConfigParser const & rhs );
        Root Rootparser(std::string file);
    private:
    
        void strTabParser(std::string status,std::string line, T &root);
        void strParser(std::string status,std::string line, T &root);
        void strTabPortParser(std::string status,std::string line, T &root);
        void mapParser(std::string status,std::string line, T &root);
        void intParser(std::string status,std::string line, T &root);
        void setIndex(std::string status,std::string line, T &root);
        void setRoot(std::string status,std::string line, T &root);
        void setErrors(std::string status,std::string line, T &root);
        void setBodySizeLimit(std::string status,std::string line, T &root);
        void setBodySizeLimit(std::string status,std::string line, T &root);
        void setAutoIndex(std::string status,std::string line, T &root);
        void setUploadDirectory(std::string status,std::string line, T &root);
        void setAllowedMethods(std::string status,std::string line, T &root);
        void setServerName(std::string status,std::string line, T &root);
        void setListen(std::string status,std::string line, T &root);
        void setRedirection(std::string status,std::string line, T &root);
        void setLocation(std::string status,std::string line, T &root);
        void setCgiPath(std::string status,std::string line, T &root);
        void setCgiExt(std::string status,std::string line, T &root);

};

#endif