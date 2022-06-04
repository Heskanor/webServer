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
    std::cout <<"shit" << std::endl;
    for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::vector<Server> servers = r1.get_servers();
    
    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        std::cout << "Server ___________" << std::endl;
        std::cout << "Server name :" << it->get_server_name() << std::endl;
        std::cout << "Listen address :"<<it->get_listenAddress()<< std::endl;
        std::cout << "Listen port :"<<it->get_listenPort() << std::endl;
        std::cout << "bodysize limit :"<<it->get_bodySizeLimit() << std::endl;
        std::vector<Location> locations = it->get_locations();
        for (std::vector<Location>::iterator it2 = locations.begin(); it2 != locations.end(); ++it2)
        {
            std::cout << "Location ___________" << std::endl;
            std::cout << it2->get_path() << std::endl;
            std::cout << it2->get_root() << std::endl;
            std::cout << it2->get_cgi_path() << std::endl;
            std::vector<std::string> cgi_ext = it2->get_cgi_ext();
            for (std::vector<std::string>::iterator it3 = cgi_ext.begin(); it3 != cgi_ext.end(); ++it3)
            {
                std::cout << *it3 << std::endl;
            }
        }

    }
    return 0;
}