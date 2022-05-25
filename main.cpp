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

bool isComment(std::string line)
{
    int i = 0;
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    if (line[i] == '#')
        return true;
    return false;
}

void skipSpaces(std::string &line)
{
    int i = 0;
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(0, i);
}
// i is the token length
void skipFirstToken(std::string &line,int i)
{
    while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
        i++;
    line.erase(0, i);
}

int main()
{
    std::ifstream ifs("Configfile");
    std::string line;
    size_t pos;
    std::string token;
    Root root;
    int i;
    if (ifs.is_open())
    {
        getline(ifs, line);
        //skip empty spaces
        skipSpaces(line);
        //-----------------------------------------------------
        // is root?
        std::stringstream X(line);
        getline(X, token,' ');
        if (token == "Root:")
        {
            //look for comments
            i = 5;
            while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
                i++;
            if (line[i] && line[i] != '#')
            {
                std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
                exit(1);
            }
            //-----------------------------------------------------
            std::cout << "|"<< "Good start sir :)" << "|"<<std::endl;
            while (getline(ifs, line))
            {
                if (!isComment(line))
                {
                    //skip empty spaces
                    skipSpaces(line);
                    //-----------------------------------------------------
                    // is root?
                    std::stringstream Y(line);
                    getline(Y, token,' ');
                    if (token =="index:")
                    {
                        // I'm not sure if getline will use the new trimed line or not!
                        skipFirstToken(line, token.length() - 1);
                        while (getline(Y, token, ' ') && !isComment(line))
                        {
                            root.add_index(token);
                            skipFirstToken(line, token.length() - 1);
                        }
                        //Parse index
                    }else if (token =="auto_index:")
                    {
                        /* code */
                    }else if (token =="bodySizeLimit:")
                    {
                        /* code */
                    }
                    else if (token =="bodySizeLimit:")
                    {
                        /* code */
                    }else if (token =="root:")
                    {
                        /* code */
                    }else if (token =="server:")
                    {
                        //look for comments
                        i = 7;
                        while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
                            i++;
                        if (line[i] && line[i] != '#')
                        {
                            std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
                            exit(1);
                        }
                        /* code */
                    }else
                    {
                        std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
                        exit(1);
                    }
                }
            }
        }
        else
        {
            std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
            exit(1);
        }
    }
    return 0;
}