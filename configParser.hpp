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
        std::string _keys[12];
        typedef void (ConfigParser::*directiveParser)(std::string line, Root &root);
        std::vector<directiveParser> t_directiveParser;
        ConfigParser() {}
        ConfigParser(const ConfigParser &src){}
        ~ConfigParser() {}
        ConfigParser &operator=( ConfigParser const & rhs );
        Root   Rootparser(std::string file);
    private:
        void strTabParser(std::string line, Root &root);
        void strParser(std::string line, Root &root);
        void strTabPortParser(std::string line, Root &root);
        void mapParser(std::string line, Root &root);
        void intParser(std::string line, Root &root);
        void setIndex(std::string line, Root &root);
        void setRoot(std::string line, Root &root);
        void setErrors(std::string line, Root &root);
        void setBodySizeLimit(std::string line, Root &root);
        void setBodySizeLimit(std::string line, Root &root);
        void setAutoIndex(std::string line, Root &root);
        void setUploadDirectory(std::string line, Root &root);
        void setAllowedMethods(std::string line, Root &root);
        void setServerName(std::string line, Root &root);
        void setListen(std::string line, Root &root);
        void setRedirection(std::string line, Root &root);
        void setLocation(std::string line, Root &root);
        void setCgiPath(std::string line, Root &root);
        void setCgiExt(std::string line, Root &root);

};

#endif