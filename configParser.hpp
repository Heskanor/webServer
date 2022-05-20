#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

#include <iostream>
#include <stack>
#include <list>

class ConfigParser
{
    private:
        std::string _current_line;
        std::string _cursor;
        std::string _current_key;
        std::string _previoua_key;
        


        
    public:
        ConfigParser() {}
        ConfigParser(const ConfigParser &src){}
        virtual ~ConfigParser() {}
        ConfigParser &operator=( ConfigParser const & rhs );
    
};

#endif