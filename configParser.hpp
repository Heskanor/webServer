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
    private:
        std::string _keys[12];
        typedef void (ConfigParser::*direcriveParser)(std::string line, Root &root);
        std::vector<direcriveParser> t_direcriveParser;
    public:
        ConfigParser() {}
        ConfigParser(const ConfigParser &src){}
        ~ConfigParser() {}
        ConfigParser &operator=( ConfigParser const & rhs );
        Root parser(std::string file);
        
        void strTabParser(std::string line, Root &root);
        void strParser(std::string line, Root &root);
        void strTabPortParser(std::string line, Root &root);
        void mapParser(std::string line, Root &root);
        void intParser(std::string line, Root &root);

};

#endif