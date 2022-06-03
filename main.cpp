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
    Root *r1 = new Root();
    r1 = parser.Rootparser("Configfile");
    str = r1->get_index();
    std::cout << str[1] << std::endl;
    return 0;
}