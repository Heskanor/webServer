#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/wait.h>
#include <fcntl.h>
#include "cgi.hpp"


Cgi::Cgi(std::string path, std::vector<std::string> ext)
{
    int fd; 
    
    fd = open(path.c_str(), O_RDONLY);
    if (fd == -1)
        throw std::runtime_error("Cgi::Cgi: open failed");
    close(fd);
    if (ext.size() == 0)
        throw std::runtime_error("Cgi::Cgi: no extension");
    
    _path = path;
    _ext = ext;
}

Cgi::~Cgi()
{
}

std::string Cgi::getPath()
{
    return _path;
}

std::vector<std::string> Cgi::getExt()
{
    return _ext;
}
void Cgi::setPath(std::string path)
{
    _path = path;
}

void Cgi::setExt(std::vector<std::string> ext)
{
    _ext = ext;
}

bool Cgi::isCgi(std::string path) const
{
    std::string exx;

    if(path.find(".") == std::string::npos)
        return false;
    exx = path.substr(path.find_last_of(".") + 1);// not sure aboout that +1
    if (std::find(_ext.begin(), _ext.end(), exx) != _ext.end())
        return true;
    return false;
}

void Cgi::envMaker(Request *request)
{
    setenv("SERVER_SOFTWARE", "webserver/1.1", 1);
    setenv("SERVER_NAME", (request->gethost()).c_str(), 1);
    setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
    setenv("SERVER_PORT", (request->get_port()).c_str(), 1);
    setenv("REQUEST_METHOD", (request->get_method()).c_str(), 1);
    setenv("PATH_INFO", (request->getrequestur()).c_str(), 1);
    setenv("PATH_TRANSLATED", (request->getrequestur()).c_str(), 1);
    setenv("SCRIPT_NAME", (request->getrequestur()).c_str(), 1);
    setenv("QUERY_STRING", (request->getquery()).c_str(), 1);
    setenv("REMOTE_HOST", (request->gethost()).c_str(), 1);
    setenv("REMOTE_ADDR", (request->getip()).c_str(), 1);
    setenv("AUTH_TYPE", "", 1);
    setenv("REMOTE_USER", "", 1);
    setenv("REMOTE_IDENT", "", 1);
    setenv("CONTENT_TYPE", (request->getcontenttype()).c_str(), 1);
    setenv("CONTENT_LENGTH", (request->getcontentlength()).c_str(), 1);
    setenv("HTTP_ACCEPT", (request->getaccept()).c_str(), 1);
    setenv("HTTP_USER_AGENT", (request->getuseragent()).c_str(), 1);
    // setenv("HTTP_ACCEPT_LANGUAGE", (request->getacceptlanguage()).c_str(), 1);
    // setenv("HTTP_ACCEPT_ENCODING", (request->getacceptencoding()).c_str(), 1);
    // setenv("HTTP_ACCEPT_CHARSET", (request->getacceptcharset()).c_str(), 1);
    // setenv("HTTP_HOST", (request->gethost()).c_str(), 1);
    // setenv("HTTP_REFERER", (request->getreferer()).c_str(), 1);
    // setenv("HTTP_COOKIE", (request->getcookie()).c_str(), 1);
    // setenv("HTTP_CONNECTION", (request->getconnection()).c_str(), 1);
    // setenv("HTTP_CACHE_CONTROL", (request->getcachecontrol()).c_str(), 1);
    // setenv("HTTP_ACCEPT_RANGES", (request->getacceptranges()).c_str(), 1);
    // setenv("HTTP_AUTHORIZATION", (request->getauthorization()).c_str(), 1);
    // setenv("HTTP_PRAGMA", (request->getpragma()).c_str(), 1);
    // setenv("HTTP_COOKIE2", (request->getcookie2()).c_str(), 1);
    // setenv("HTTP_EXPIRES", (request->getexpires()).c_str(), 1);
    // setenv("HTTP_FROM", (request->getfrom()).c_str(), 1);
    // setenv("HTTP_REPLYTO", (request->getreplyto()).c_str(), 1);
    // setenv("HTTP_SENDER", (request->getsender()).c_str(), 1);
    // setenv("HTTP_X_FORWARDED_FOR", (request->getxforwardedfor()).c_str(), 1);
    // setenv("HTTP_X_REQUESTED_WITH", (request->getxrequestedwith()).c_str(), 1);
    // setenv("HTTP_X_ATT_DEVICEID", (request->getxattdeviceid()).c_str(), 1);
    // setenv("HTTP_X_WAP_PROFILE", (request->getxwapprofile()).c_str(), 1);
    // setenv("HTTP_X_WAP_CLIENTID", (request->getxwapclientid()).c_str(), 1);
    // setenv("HTTP_X_OPERAMINI_PHONE_UA", (request->getxoperaminiphoneua()).c_str(), 1);
}

void Cgi::executer(Request *request, Response *response)
{
    int fd[2];
    int status;
    pid_t pid;
    std::stringstream ss;

}
