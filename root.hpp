#ifndef ROOT_HPP
# define ROOT_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
//#include "server.hpp"
#include <map>

class Server;

class Root
{
    private:
        std::vector<Server> _servers;

    protected:
        std::vector<std::string> _index;
        std::string _root;
        long long _bodySizeLimit;
        bool _autoIndex;
        std::map<std::string, std::string>  _error_map;
        std::string _uploadDirectory;
        std::vector<std::string> _allowedMethods;

    public:
        Root();
        Root(const Root &src);
        virtual ~Root();
        virtual Root &operator=( Root const & rhs );
        //geters and seters
        virtual std::string get_root();
        virtual void set_root(std::string root);
        virtual std::vector<std::string> get_index();
        virtual void set_index(std::vector<std::string> index);
        virtual void add_index(std::string index);
        virtual bool get_auto_index();
        virtual void set_auto_index(bool autoIndex);
        virtual long long get_bodySizeLimit();
        virtual void set_bodySizeLimit(long long bodySizeLimit);
        virtual std::vector<Server> get_servers();
        virtual Server get_server(int index);
        virtual void set_servers(std::vector<Server> servers);
        virtual void add_server(Server &server);
        //virtual void add_server(Server &server);
        virtual void add_error_map(std::string error, std::string error_url);
        virtual std::string get_error_map(std::string error);
        virtual std::map<std::string, std::string> get_errors_map();
        virtual std::map<std::string, std::string> get_errmap();
        virtual std::string get_upload_directory();
        virtual void set_upload_directory(std::string upload_directory);
        virtual std::vector<std::string> get_allowed_methods();
        virtual void add_allowed_method(std::string method);
        virtual void set_allowed_methods(std::vector<std::string> allowed_methods);


};

#endif