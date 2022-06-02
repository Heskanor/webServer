#ifndef LOCATION_HPP
# define LOCATION_HPP
#include <iterator>
#include <map>
#include "server.hpp"
// #include "root.hpp"


class Location : public virtual Server
{
    private:
        std::string _path;
        std::string _cgi_path;
        std::vector<std::string> _cgi_ext;
        
    public:
        Location();
        Location(const Location &src);
        ~Location();
        Location &operator=( Location const & rhs );
        //geters and seters
        std::string get_path();
        void set_path(std::string path);
        std::string get_cgi_path();
        void set_cgi_path(std::string cgi_path);
        std::vector<std::string> get_cgi_ext();
        void set_cgi_ext(std::vector<std::string> cgi_ext);
        void add_cgi_ext(std::string ext);
};
 
#endif