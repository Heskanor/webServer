#ifndef LOCATION_HPP
# define LOCATION_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>



class Location
{
    private:
        std::string _path;
        std::vector<std::string> _index;
        bool _auto_index;
        std::string _error500;
        std::string _error502;
        std::string _upload_directory;
        std::vector<std::string> _allowed_methods;
        std::string _cgi_path;
        std::vector<std::string> _cgi_ext;
        
        
    public:
        Location() {}
        Location(const Location &src){}
        virtual ~Location() {}
        Location &operator=( Location const & rhs );
    
};

#endif