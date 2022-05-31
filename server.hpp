#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include "location.hpp"
#include "root.hpp"

class Root;
class Server : public Root
{
    private:
        std::string _server_name;
        std::string _listenPort;
        std::string _listenAddress;
        std::vector<Location> _locations;
    protected:
        std::map<int, std::string>  _redirections;
    public:
        Server() {}
        Server(const Server &src){}
        virtual ~Server() {}
        Server &operator=( Server const & rhs );
        //geters and seters
        std::string get_server_name();
        void set_server_name(std::string name);
        std::string get_listenAddress();
        std::string get_listenPort();
        void set_listenAddress(std::string address);
        void set_listenPort(std::string port);
        std::map<int, std::string>  get_redirections();
        std::string get_redirection(int code);
        void add_redirect_map(int code, std::string url);
        std::vector<Location> get_locations();
        void add_location(Location location);
        Location get_location(int index);
};

#endif