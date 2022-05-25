#ifndef LOCATION_HPP
# define LOCATION_HPP


#include <iterator>
#include <map>
#include "server.hpp"



class Location : public Server
{
    private:
        std::string _path;
        
        
        std::vector<std::string> _allowed_methods;
        std::string _cgi_path;
        std::vector<std::string> _cgi_ext;
        
    public:
        Location() {}
        Location(const Location &src){}
        virtual ~Location() {}
        Location &operator=( Location const & rhs );
        //geters and seters
        std::string get_path();
        void set_path(std::string path);
        std::vector<std::string> get_index();
        void set_index(std::vector<std::string> index);
        bool get_auto_index();
        void set_auto_index(bool auto_index);
        std::string get_error_map(int error);
        void set_error_map(int error, std::string error_message);
        std::string get_upload_directory();
        void set_upload_directory(std::string upload_directory);
        std::vector<std::string> get_allowed_methods();
        void set_allowed_methods(std::vector<std::string> allowed_methods);
        std::string get_cgi_path();
        void set_cgi_path(std::string cgi_path);
        std::vector<std::string> get_cgi_ext();
        void set_cgi_ext(std::vector<std::string> cgi_ext);
        //methods
        void add_index(std::string index);
        void add_allowed_method(std::string method);
        void add_cgi_ext(std::string ext);
};
 
#endif