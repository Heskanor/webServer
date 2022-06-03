#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "root.hpp"
#include "server.hpp"
#include "location.hpp"
#include "configParser.hpp"

int main()
{
    ConfigParser parser;
    std::vector<std::string> str;
    Root r1;
    Server s;
    r1 = parser.Rootparser("Configfile");
    str = r1.get_index();
    for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::vector<Server> servers = r1.get_servers();
    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        std::cout << it->get_listenAddress()<< std::endl;
        std::cout<< it->get_listenPort() << std::endl;
    }
    return 0;
}