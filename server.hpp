#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include "location.hpp"

class Server : virtual public Root
{
    private:
        std::string _server_name;
        int _port;
        std::vector<Location> _locations;
    public:
        Server() {}
        Server(const Server &src){}
        virtual ~Server() {}
        Server &operator=( Server const & rhs );
        //geters and seters
        std::string get_server_name();
        void set_server_name(std::string name);
        int get_port();
        void set_port(int port);
        std::vector<Location> get_locations();
        void add_location(Location location);
};

#endif