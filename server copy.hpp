#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

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
        bool _autoIndex;
        std::string _error500;
        std::string _error502;
        std::string _uploadDir;
        std::vector<std::string> _methods;
        std::string _uploadDir;
        std::string _cgiPath;
        std::vector<std::string> _cgiExt;
        
    public:
        Location() {}
        Location(const Location &src){}
        virtual ~Location() {}
        Location &operator=( Location const & rhs );
    
};

#endif