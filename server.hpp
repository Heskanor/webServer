#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

#include <iostream>
#include <stack>
#include <list>

class Server
{
    private:
        std::string _name;
        std::string _listen;
        
    public:
        Server() {}
        Server(const Server &src){}
        virtual ~Server() {}
        Server &operator=( Server const & rhs );
    
};

#endif