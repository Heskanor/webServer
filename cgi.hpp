#ifndef CGI_HPP
# define CGI_HPP

#include <iostream>
#include "Request.hpp"

class Cgi
{
    private:
        std::string _root;
        std::string _server;
    public:
    Cgi(std::string path, std::vector<std::string> ext);
    ~Cgi();
    std::string getPath();
    void setPath(std::string path);
    void setExt(std::vector<std::string> ext);
    std::vector<std::string> getExt();
    bool isCgi(std::string path) const; 
    void envMaker(Request *request);
    //I may need a cgi checker here !?
    // Cgi checker(std::string path);
    void executer(Request *request, Resonse *response);




};

#endif