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
// int main()
// {
   
//     std::ifstream ifs("Configfile");
//     std::string line;
//     size_t pos;
//     std::string token;

//     if (ifs.is_open())
//     {
//         //root parsing 
//         while (getline(X, token,' ' && token.find("index:") == std::string::npos)
//         {
//             std::cout <<"a_ " << token << std::endl; //call index setter

//                 }
//         while (getline(ifs, line) && line.find("server:") == std::string::npos)
//         {
//             std::stringstream X(line);
//             if ((pos = line.find("index:")) != std::string::npos)
//             {
//                 //std::cout << line << std::endl;
//                 //std::cout << pos << std::endl;
//                 while (getline(X, token,' '))
//                 {
//                     if (token != "" && token.find("index:") == std::string::npos)
//                         std::cout <<"a_ " << token << std::endl; //call index setter

//                 }
//                 //line.erase(pos, line.find("\n") + 1);
//                 std::cout << line << std::endl;
//             }
//         }
//     }
//     return 0;
// }

int main()
{
   
    std::ifstream ifs("Configfile");
    std::string line;
    size_t pos;
    std::string token;
    int i;
    if (ifs.is_open())
    {
        getline(ifs, line);
        //skip empty spaces
        i = 0;
        while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
            i++;
        line.erase(0, i);
        //-----------------------------------------------------
        // is root?
        std::stringstream X(line);
        getline(X, token,' ');
        if (token == "Root:")
        {
            i = 5;
            while ( (line[i] == 32 || (line[i] < 14 && line[i] > 8))&& i< line.length())
                i++;
            if (line[i] && line[i] != '#')
            {
                std::cout << "|"<< "FUCK OFF" << "|"<<std::endl;
                exit(1);
            }
            std::cout << "|"<< "Good start sir :)" << "|"<<std::endl;
            while (getline(ifs, line))
            {

            }
        }
        else
        {
            std::cout << "|"<< "I hate you" << "|"<<std::endl;
        }
    }
    return 0;
}