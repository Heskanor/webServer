#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include <map>

#include "root.hpp"
class Location;

class Server : public virtual Root
{
    private:
        std::string _server_name;
        int _listenPort;
        std::string _listenAddress;
        std::vector<Location> _locations;
    protected:
        std::map<std::string, std::string>  _redirections;
    public:
        Server();
        Server(const Server &src);
        ~Server();
        virtual Server &operator=( Server const & rhs );
        virtual //geters and seters
        std::string get_server_name();
        virtual void set_server_name(std::string name);
        virtual std::string get_listenAddress();
        virtual int get_listenPort();
        virtual void set_listenAddress(std::string address);
        virtual void set_listenPort(std::string port);
        virtual std::map<std::string, std::string>  get_redirections();
        virtual std::string get_redirection(std::string code);
        virtual void add_redirect_map(std::string code, std::string url);
        virtual std::vector<Location> get_locations();
        void add_location(Location &location);
        virtual Location get_location(int index);
};

#endif