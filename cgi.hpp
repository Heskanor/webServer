#ifndef CGI_HPP
# define CGI_HPP

#include <iostream>
#include "Request.hpp"
#include "Response.hpp"
#include "location.hpp"

class Cgi
{
    private:
        std::string _path;
        std::vector<std::string> _ext;
    public:
    Cgi(std::string path, std::vector<std::string> ext);// done
    ~Cgi(); //done?
    std::string getPath();
    void setPath(std::string path);
    void setExt(std::vector<std::string> ext);
    std::vector<std::string> getExt();
    bool isCgi(std::string path) const; 
    void envMaker(Request *request, Location &location);
    //I may need a cgi checker here !?
    // Cgi checker(std::string path);
    void executer(Request *request, Response *response, Location &location);




};

#endif