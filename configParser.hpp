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
        std::string _serverkeys[10];
        std::string _locationkeys[10];
        std::vector<rootParser> t_rootParser;
        std::vector<serverParser> t_serverParser;
        std::vector<locationParser> t_locationParser;
        ConfigParser();
        ConfigParser(const ConfigParser &src);
        ~ConfigParser();
        ConfigParser &operator=( ConfigParser const & rhs );
        Root *Rootparser(std::string file);
    private:
    
        void strTabParser(std::string status,std::string line, std::vector<std::string> &str);//done
        void strParser(std::string status,std::string line, std::string &root);//done
        void intParser(std::string status,std::string line, int &size);//done
        //void mapParser(std::string status,std::string line, Root &root);//done
        // void mapErrParser(std::string status,std::string line, Root &root);//done
        void setIndex(std::string status,std::string line, Root &root);//done
        void setRoot(std::string status,std::string line, Root &root);//done
        void setErrors(std::string status,std::string line, Root &root);//done
        void setBodySizeLimit(std::string status,std::string line, Root &root);//done
        void setAutoIndex(std::string status,std::string line, Root &root);//done
        void setUploadDirectory(std::string status,std::string line, Root &root);//done
        void setAllowedMethods(std::string status,std::string line, Root &root);//done

        void setIndex(std::string status,std::string line, Server &root);//done
        void setRoot(std::string status,std::string line, Server &root);//done
        void setErrors(std::string status,std::string line, Server &root);//done
        void setBodySizeLimit(std::string status,std::string line, Server &root);//done
        void setAutoIndex(std::string status,std::string line, Server &root);//done
        void setUploadDirectory(std::string status,std::string line, Server &root);//done
        void setAllowedMethods(std::string status,std::string line, Server &root);//done
        void setServerName(std::string status,std::string line, Server &root);//done
        void setListen(std::string status,std::string line, Server &root);//done
     
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