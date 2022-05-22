#include "configParser.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
//webserv config file parser
ConfigParser::ConfigParser()
{
    _current_line = "";
    _cursor = "";
    _current_key = "";
    _previous_key = "";
}

void ConfigParser::set_current_line(std::string line)
{
    _current_line = line;
}

void ConfigParser::set_cursor(std::string cursor)
{
    _cursor = cursor;
}

void ConfigParser::set_current_key(std::string key)
{
    _current_key = key;
}

void ConfigParser::set_previous_key(std::string key)
{
    _previous_key = key;
}

std::string ConfigParser::get_current_key()
{
    return _current_key;
}

std::string ConfigParser::get_current_line()
{
    return _current_line;
}

std::string ConfigParser::get_cursor()
{
    return _cursor;
}

std::string ConfigParser::get_previous_key()
{
    return _previous_key;
}

Root parser(std::string file)
{
    Root root;
    std::ifstream configFile(file);
    std::string line;
    std::string cursor;
    std::string current_key;   
    std::string previous_key;
    std::string current_line;
    std::string root_name;
    std::string token;
    std::vector<std::string> index;
    bool auto_index = false;
    int bodySizeLimit = 0;
    std::vector<Server> servers;
    size_t pos;
    if (configFile.is_open())
    {
        while (getline(configFile, line) && line.find("server:") == std::string::npos)
        {
            std::stringstream X(line);
            if ((pos = line.find("index:")) != std::string::npos)
            {
                while (getline(X, token,' '))
                {
                    if (token != "" && token.find("index:") == std::string::npos)
                        root.add_index(token); //call index setter
                }
            }
            else if ((pos = line.find("auto_index:")) != std::string::npos)
            {
                getline(X, token,' ');
                while (getline(X, token,' '))
                {
                    if (token != "")
                    {
                        if (token.find("true") == std::string::npos && token.find("false") == std::string::npos)
                        {
                            std::cout << "Error: Auto-Index must be true or false" << std::endl;
                            exit(1);
                        }
                        else if (token.find("true") != std::string::npos)
                            root.set_auto_index(true);
                        else if (token.find("false") != std::string::npos)
                            root.set_auto_index(false);
                    }
                }
            }
            else if ((pos = line.find("bodySizeLimit:")) != std::string::npos)
            {
                getline(X, token,' ');
                if (getline(X, token,' ') && (token.find_first_not_of("0123456789") == std::string::npos))
                    root.set_bodySizeLimit(std::stoi(token));
                else
                {
                    std::cout << "Error: BodySizeLimit must be a number" << std::endl;
                    exit(1);
                }
            }
            if ((pos = line.find("root:")) != std::string::npos)
            {
                getline(X, token,' ');
                if (getline(X, token,' '))
                    root.set_root(token);
                else
                {
                    std::cout << "Error: Root must be a string" << std::endl;
                    exit(1);
                }
            }
        }
        if (line.find("server:") != std::string::npos)
        {
            while(getline(configFile, line))
            {
                if (line.find("server:") != std::string::npos)
                {
                    Server server;
                    std::stringstream X(line);
                    getline(X, token,' ');
                    if (getline(X, token,' '))
                        server.set_name(token);
                    else
                    {
                        std::cout << "Error: Server name must be a string" << std::endl;
                        exit(1);
                    }
                    getline(X, token,' ');
                    if (getline(X, token,' '))
                        server.set_port(std::stoi(token));
                    else
                    {
                        std::cout << "Error: Server port must be a number" << std::endl;
                        exit(1);
                    }
                    getline(X, token,' ');
                    if (getline(X, token,' '))
                        server.set_ip(token);
                    else
                    {
                        std::cout << "Error: Server ip must be a string" << std::endl;
                        exit(1);
                    }
                    getline(X, token,' ');
                    if (getline(X, token,' '))
                        server.set_root(token);
                    else
                    {
                        std::cout << "Error: Server root must be a string" << std::endl;
                        exit(1);
                    }
                    getline(X, token,' ');
                    if (getline(X, token,' '))
                        server.set_index(token);
                    else
                    {
                        std::cout << "Error: Server index must be a string" << std::endl;
                        exit(1);
                    }
                    getline(X, token,' ');
                    if (getline(X, token,' '))
                    {
                        if (token.find("true") == std::string::npos && token.find("false") == std::string::npos)
                        {
                            std::cout << "Error: Server auto-index must be true or false" << std::
        }

    }   
}

// current_line = line;
//             cursor = line;
//             while ((pos = cursor.find("index")) != std::string::npos)
//             {
//                 cursor.erase(pos, cursor.find(" ") + 1);
//             }
//             if (cursor.find("#") != std::string::npos)
//             {
//                 cursor.erase(cursor.find("#"), cursor.length());
//             }
//             if (cursor.find("=") != std::string::npos)
//             {
//                 current_key = cursor.substr(0, cursor.find("="));
//                 cursor.erase(0, cursor.find("=") + 1);
//                 if (current_key == "root")
//                 {
//                     root_name = cursor;
//                     root.set_root(root_name);
//                 }
//                 else if (current_key == "auto_index")
//                 {
//                     if (cursor == "true")
//                     {
//                         auto_index = true;
//                     }
//                     else
//                     {
//                         auto_index = false;
//                     }
//                     root.set_auto_index(auto_index);
//                 }
//                 else if (current_key == "index")
//                 {
//                     index.push_back(cursor);
//                     root.set_index(index);
//                 }
//                 else if (current_key == "body_size_limit")
//                 {
//                     bodySizeLimit = std::stoi(cursor);
//                     root.set_bodySizeLimit(bodySizeLimit);
//                 }
//                 else
//                 {
//                     Server server;
//                     server.set_name(current_key);
//                     server.set_root(root_name);
//                     server.set_auto_index(auto_index);
//                     server.set_index(index);
//                     server.set_bodySizeLimit(bodySizeLimit);
//                     servers.push_back(server);
//                 }
//             }
//         }
//         root.set_servers(servers);
//         configFile.close();