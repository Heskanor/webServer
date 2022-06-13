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
    Root r1;;
    Server s;
    r1 = parser.Rootparser("Configfile");
    str = r1.get_index();
    std::cout <<"Root ___________" << std::endl;
    std::cout <<" Index:";
    for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); ++it)
    {
        std::cout << " " << *it;
    }
    std::cout << "\n root : " << r1.get_root() << std::endl;
    std::cout << " bodysizelimit : " << r1.get_bodySizeLimit() << std::endl;
    std::cout << " autoIndex : " << r1.get_auto_index() << std::endl;

    //error map iterator
    std::map<std::string, std::string>::iterator it;
    std::map<std::string, std::string> error_map = r1.get_errmap();
    std::cout << " error map : " << std::endl;
    for (it = error_map.begin(); it != error_map.end(); ++it)
    {
        std::cout << " " << it->first << " " << it->second << std::endl;
    }
    std::cout << " autoIndex : " << r1.get_auto_index() << std::endl;
    std::vector<Server> servers = r1.get_servers();
    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        std::cout << std::endl <<" Server ___________" << std::endl;
        str = it->get_index();
        std::cout <<"   Index:";
        for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); ++it)
        {
            std::cout << " " << *it;
        }
        std::cout << "\n   Server name :" << it->get_server_name() << std::endl;
        std::cout << "   Listen address :"<<it->get_listenAddress()<< std::endl;
        std::cout << "   Listen port :"<<it->get_listenPort() << std::endl;
        std::cout << "   bodysizelimit :"<<it->get_bodySizeLimit() << std::endl;
        std::vector<Location> locations = it->get_locations();
        //int i = 0;
        for (std::vector<Location>::iterator it2 = locations.begin(); it2 != locations.end(); ++it2)
        {
            // std::cout <<">>" <<i<<"<<"<<std::endl;
            // i++;
            std::cout << "\n |__Location ___________" << std::endl;
            std::cout << "     body size limit :" << it2->get_bodySizeLimit() << std::endl;
            std::cout << "     path :"<< it2->get_path() << std::endl;
            std::cout << "     root :"<< it2->get_root() << std::endl;
            std::cout << "     errorPage 501:"<< it2->get_error_map("501") << std::endl;
            std::pair<std::string, std::string> lord = it2->get_redirection();
            std::cout << "     return :"<< lord.first << std::endl;
            std::cout << "     cgi path :"<< it2->get_cgi_path() << std::endl;
            std::vector<std::string> cgi_ext = it2->get_cgi_ext();
            std::cout << "     cgi ext :"<< it2->get_cgi_path();
            for (std::vector<std::string>::iterator it3 = cgi_ext.begin(); it3 != cgi_ext.end(); ++it3)
            {
                std::cout << *it3 << " ";
            }
        }
    }
    //system("leaks webserver");
    return 0;
}