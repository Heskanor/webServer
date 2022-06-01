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
        Root *Rootparser(std::string file);
    private:
    
        void strTabParser(std::string status,std::string line, Root &lvl);// done 
        void strParser(std::string status,std::string line, Root &root);//done
        void mapParser(std::string status,std::string line, Root &root);//done
        void mapErrParser(std::string status,std::string line, Root &root);//done
        void intParser(std::string status,std::string line, Root &root);//done
        void setIndex(std::string status,std::string line, Root &root);//done
        void setRoot(std::string status,std::string line, Root &root);//done
        void setErrors(std::string status,std::string line, Root &root);//done
        void setBodySizeLimit(std::string status,std::string line, Root &root);//done
        void setAutoIndex(std::string status,std::string line, Root &root);//done
        void setUploadDirectory(std::string status,std::string line, Root &root);//done
        void setAllowedMethods(std::string status,std::string line, Root &root);//done

        void strTabParser(std::string status,std::string line, Server &lvl);// done 
        void strParser(std::string status,std::string line, Server &root);//done
        void mapParser(std::string status,std::string line, Server &root);//done
        void mapErrParser(std::string status,std::string line, Server &root);//done
        void intParser(std::string status,std::string line, Server &root);//done
        void setIndex(std::string status,std::string line, Server &root);//done
        void setRoot(std::string status,std::string line, Server &root);//done
        void setErrors(std::string status,std::string line, Server &root);//done
        void setBodySizeLimit(std::string status,std::string line, Server &root);//done
        void setAutoIndex(std::string status,std::string line, Server &root);//done
        void setUploadDirectory(std::string status,std::string line, Server &root);//done
        void setAllowedMethods(std::string status,std::string line, Server &root);//done
        void setServerName(std::string status,std::string line, Server &root);//done
        void setListen(std::string status,std::string line, Server &root);//done
        void setRedirection(std::string status,std::string line, Server &root);//done
        void setLocation(std::string status,std::string line, Server &root);//done
        void setCgiPath(std::string status,std::string line, Server &root);
        void setCgiExt(std::string status,std::string line, Server &root);

        void strTabParser(std::string status,std::string line, Location &lvl);// done 
        void strParser(std::string status,std::string line, Location &root);//done
        void mapParser(std::string status,std::string line, Location &root);//done
        void mapErrParser(std::string status,std::string line, Location &root);//done
        void intParser(std::string status,std::string line, Location &root);//done
        void setIndex(std::string status,std::string line, Location &root);//done
        void setRoot(std::string status,std::string line, Location &root);//done
        void setErrors(std::string status,std::string line, Location &root);//done
        void setBodySizeLimit(std::string status,std::string line, Location &root);//done
        void setAutoIndex(std::string status,std::string line, Location &root);//done
        void setUploadDirectory(std::string status,std::string line, Location &root);//done
        void setAllowedMethods(std::string status,std::string line, Location &root);//done
        void setRedirection(std::string status,std::string line, Location &root);//done
        void setLocation(std::string status,std::string line, Location &root);//done
        void setCgiPath(std::string status,std::string line, Location &root);
        void setCgiExt(std::string status,std::string line, Location &root);
};

#endif