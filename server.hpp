#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include "location.hpp"

class Server
{
    private:
        std::string server_name;
        std::vector<std::string> _index;
        bool _autoIndex;
        std::string _root;
        int _port;
        int _bodySizeLimit;
        std::vector<Location> _locations;
        
    public:
        Server() {}
        Server(const Server &src){}
        virtual ~Server() {}
        Server &operator=( Server const & rhs );
    
};

#endif