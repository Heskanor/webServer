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
    Root *r1 = new Root();
    r1 = parser.Rootparser("Configfile");

    return 0;
}