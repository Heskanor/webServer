#ifndef ROOT_HPP
# define ROOT_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include "location.hpp"

class Root
{
    private:
        std::vector<Server> _servers;

    protected:
        std::string _root;
        int _bodySizeLimit;
        bool _auto_index;
        std::vector<std::string> _index;

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
        bool get_autoIndex();
        void set_autoIndex(bool autoIndex);
        std::string get_root();
        void set_root(std::string root);
        int get_bodySizeLimit();
        void set_bodySizeLimit(int bodySizeLimit);
        void parser(std::string file);
};

#endif