#ifndef ROOT_HPP
# define ROOT_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include "server.hpp"

class Root
{
    protected:
        std::vector<std::string> _index;
        std::string _root;
        std::map<int, std::string>  _error_map;
        int _bodySizeLimit;
        bool autoIndex;
        std::string _uploadDirectory;
        std::vector<std::string> _allowedMethods;
        std::vector<Server> _servers;

    public:
        Root() {}
        Root(const Root &src){}
        virtual ~Root() {}
        Root &operator=( Root const & rhs );
        //geters and seters
        std::string get_Root();
        void set_Root(std::string name);
        std::vector<std::string> get_index();
        void set_index(std::vector<std::string> index);
        void add_index(std::string index);
        bool get_auto_index();
        void set_auto_index(bool autoIndex);
        std::string get_root();
        void set_root(std::string root);
        int get_bodySizeLimit();
        void set_bodySizeLimit(int bodySizeLimit);
        std::vector<Server> get_servers();
        Server get_server(int index);
        void set_servers(std::vector<Server> servers);
        void add_server(Server server);
};

#endif