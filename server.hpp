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
        std::string _root;
        int _port;
        int _bodySizeLimit;
        std::vector<Location> _locations;

    protected: // inherited by Location
        bool _auto_index;
        std::vector<std::string> _index;

    public:
        Server() {}
        Server(const Server &src){}
        virtual ~Server() {}
        Server &operator=( Server const & rhs );
        //geters and seters
        std::string get_server_name();
        void set_server_name(std::string name);
        std::vector<std::string> get_index();
        void set_index(std::vector<std::string> index);
        bool get_autoIndex();
        void set_autoIndex(bool autoIndex);
        std::string get_root();
        void set_root(std::string root);
        int get_port();
        void set_port(int port);
        int get_bodySizeLimit();
        void set_bodySizeLimit(int bodySizeLimit);
        std::vector<Location> get_locations();
        void set_locations(std::vector<Location> locations);
        //methods
        void add_location(Location location);
        void add_location(std::string path, std::string root, std::vector<std::string> index, bool autoIndex, std::string error500, std::string error502, std::string upload_directory, std::vector<std::string> allowed_methods, std::string cgi_path, std::vector<std::string> cgi_ext);
        // void add_location(std::string path, std::string root, std::vector<std::string> index, bool autoIndex, std::string error500, std::string error502, std::string upload_directory, std::vector<std::string> allowed_methods);
        // void add_location(std::string path, std::string root, std::vector<std::string> index, bool autoIndex, std::string error500, std::string error502);
        // void add_location(std::string path, std::string root, std::vector<std::string> index, bool autoIndex);
        // void add_location(std::string path, std::string root, std::vector<std::string> index);
        // void add_location(std::string path, std::string root);
        // void add_location(std::string path);
        // void add_location();
    
};

#endif