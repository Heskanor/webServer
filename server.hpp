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
        std::vector<std::string> _server_name;
        int _listenPort;
        std::string _listenAddress;
        std::vector<Location> _locations;
    protected:
        std::pair<std::string, std::string> _redirection;

        //std::map<std::string, std::string>  _redirections;
        // redriction.first = 500;
        // redriction.second = "path";
    public:
        Server();
        Server(const Server &src);
        Server(Root &src);
        ~Server();
        virtual Server &operator=( Server const & rhs );
        void clear(Root &src);
        bool check_empty();
        //geters and seters
        virtual std::vector<std::string> get_server_name();
        virtual void set_server_name(std::vector<std::string> name);
        virtual std::string get_listenAddress();
        virtual void set_listenAddress(std::string address);
        virtual int get_listenPort();
        virtual void set_listenPort(std::string port);
        virtual std::pair<std::string, std::string> get_redirection();
        virtual void set_redirection(std::string code, std::string url);
        std::vector<Location> get_locations();
        void add_location(Location &location);
        Location get_location(int index);
		void insert_location(Location &location);
};

#endif