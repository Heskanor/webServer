#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

#include <iostream>
#include <stack>
#include <list>
#include "server.hpp"
#include "location.hpp"
#include "root.hpp"

template <class T>
class ConfigParser
{
    public:
        // template <typedef T>
        typedef void (ConfigParser::*directiveParser)(std::string token,std::string line, T &lvl);
        std::string _keys[12];
        std::vector<directiveParser> t_directiveParser;
        ConfigParser();
        ConfigParser(const ConfigParser &src);
        ~ConfigParser();
        ConfigParser &operator=( ConfigParser const & rhs );
        Root Rootparser(std::string file);
    private:
    
        void strTabParser(std::string status,std::string line, T &lvl);// done 
        void strParser(std::string status,std::string line, T &root);//done
        void mapParser(std::string status,std::string line, T &root);//done
        void mapErrParser(std::string status,std::string line, T &root);//done
        void intParser(std::string status,std::string line, T &root);//done
        void setIndex(std::string status,std::string line, T &root);//done
        void setRoot(std::string status,std::string line, T &root);//done
        void setErrors(std::string status,std::string line, T &root);//done
        void setBodySizeLimit(std::string status,std::string line, T &root);//done
        void setAutoIndex(std::string status,std::string line, T &root);//done
        void setUploadDirectory(std::string status,std::string line, T &root);//done
        void setAllowedMethods(std::string status,std::string line, T &root);//done
        void setServerName(std::string status,std::string line, T &root);//done
        void setListen(std::string status,std::string line, T &root);//done
        void setRedirection(std::string status,std::string line, T &root);//done
        void setLocation(std::string status,std::string line, T &root);//done
        void setCgiPath(std::string status,std::string line, T &root);
        void setCgiExt(std::string status,std::string line, T &root);
};

#endif