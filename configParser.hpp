#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

#include <iostream>
#include <stack>
#include <list>
#include "server.hpp"


class ConfigParser
{
    private:
        std::string _current_line;
        std::string _cursor;
        std::string _current_key;
        std::string _previous_key;
        


        
    public:
        ConfigParser() {}
        ConfigParser(const ConfigParser &src){}
        ~ConfigParser() {}
        ConfigParser &operator=( ConfigParser const & rhs );
        Server * parser(std::string file);
        std::string get_current_key();
        std::string get_current_line();
        std::string get_cursor();
        std::string get_previous_key();
        void set_previous_key(std::string key);
        void set_current_key(std::string key);
        void set_current_line(std::string line);
        void set_cursor(std::string cursor);
        Server

};

#endif