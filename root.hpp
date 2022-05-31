#ifndef ROOT_HPP
# define ROOT_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include <map>

class Server;

class Root
{
    private:
        std::vector<Server> _servers;

    protected:
        std::vector<std::string> _index;
        std::string _root;
        int _bodySizeLimit;
        bool _autoIndex;
        std::map<int, std::string>  _error_map;
        std::string _uploadDirectory;
        std::vector<std::string> _allowedMethods;

    public:
        Root() {}
        // Root(const Root &src){}
        virtual ~Root() {}
        Root &operator=( Root const & rhs );
        //geters and seters
        std::string get_root();
        void set_root(std::string root);
        std::vector<std::string> get_index();
        void set_index(std::vector<std::string> index);
        void add_index(std::string index);
        bool get_auto_index();
        void set_auto_index(bool autoIndex);
        int get_bodySizeLimit();
        void set_bodySizeLimit(int bodySizeLimit);
        std::vector<Server> get_servers();
        Server get_server(int index);
        void set_servers(std::vector<Server> servers);
        void add_server(Server server);
        void add_error_map(int error, std::string error_url);
        std::string get_error_map(int error);
        std::string get_upload_directory();
        void set_upload_directory(std::string upload_directory);
        std::vector<std::string> get_allowed_methods();
        void set_allowed_methods(std::vector<std::string> allowed_methods);


};

#endif