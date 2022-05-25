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
        void (ConfigParser::direcriveParser[12])(std::string line);
    public:
        ConfigParser() {}
        ConfigParser(const ConfigParser &src){}
        ~ConfigParser() {}
        ConfigParser &operator=( ConfigParser const & rhs );
        Root parser(std::string file);
        
        void strTabParser(std::string line);
        void strParser(std::string line);
        void strTabPortParser(std::string line);
        void mapParser(std::string line);
        void intParser(std::string line);

};  

#endif