#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>  


//     Root root;
//     std::ifstream configFile(file);
//     std::string line;
//     std::string cursor;
//     std::string current_key;   
//     std::string previous_key;
//     std::string current_line;
//     std::string root_name;
//     std::vector<std::string> index;
//     bool auto_index = false;
//     int bodySizeLimit = 0;
//     std::vector<Server> servers;
//     size_t pos;
//     if (configFile.is_open())
//     {
//         while (getline(configFile, line))
//         {
//             current_line = line;
//             cursor = line;
//             while ((pos = cursor.find("index")) != std::string::npos)
//             {
//                 cursor.erase(pos, cursor.find(" ") + 1);
//             }
//             if (cursor.find("#") != std::string::npos)
//             {
//                 cursor.erase(cursor.find("#"), cursor.length());
//             }
//         
//                 }
//             }
//         }
//         root.set_servers(servers);
//         configFile.close();
// }
int main()
{
   
    std::ifstream ifs("Configfile");
    std::string line;
    size_t pos;
    std::string token;

    if (ifs.is_open())
    {
        //root parsing 
        while (getline(ifs, line) && line.find("server:") == std::string::npos)
        {
            std::stringstream X(line);
            if ((pos = line.find("index:")) != std::string::npos)
            {
                //std::cout << line << std::endl;
                //std::cout << pos << std::endl;
                while (getline(X, token,' '))
                {
                    if (token != "" && token.find("index:") == std::string::npos)
                        std::cout <<"a_ " << token << std::endl; //call index setter

                }
                //line.erase(pos, line.find("\n") + 1);
                std::cout << line << std::endl;
            }
        }
    }
    return 0;
}