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
    //ConfigParser<Root> parser;
    Root *r1 = new Root();
    Server *r2 = new Server();
    Location *r = new Location();

    return 0;
}