#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>



class Server
{
    private:
        std::string _name;
        std::vector<std::string> _index;
        bool _autoIndex;
        std::string _root;
        int _port;
        int _bodySizeLimit;
        


        
    public:
        Server() {}
        Server(const Server &src){}
        virtual ~Server() {}
        Server &operator=( Server const & rhs );
    
};

#endif