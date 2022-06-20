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
std::string get_querrystring(std::string path)
{
    std::string querrystring;
    if (path.find("?") != std::string::npos)
    {
        querrystring = path.substr(path.find("?") + 1);
        return querrystring;
    }
}

void Cgi::envMaker(Request *request, Location &location)
{
    std::string scriptname = location.get_root() + _path;


    //setenv("AUTH_TYPE", "", 1);
    setenv("CONTENT_LENGTH", (request->getcontentlenght()).c_str(), 1);
    setenv("CONTENT_TYPE", (request->getcontenttype()).c_str(), 1); // need content type geter
    setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    setenv("PATH_INFO", ((request->get_requestur())).substr(0,request->get_requestur().find_first_of('?')).c_str(), 1); // subtr query string
    setenv("PATH_TRANSLATED", ((request->get_requestur())).substr(0,request->get_requestur().find_first_of('?')).c_str(), 1); // dir b7al path info
    setenv("QUERY_STRING", get_querrystring(request->get_requestur()).c_str(), 1);// after ?
    setenv("REMOTE_ADDR", "localhost", 1);
    setenv("REMOTE_HOST", (request->gethost()).c_str(), 1);// maybe like remote address
    // setenv("REMOTE_IDENT", "", 1);
    // setenv("REMOTE_USER", "", 1);
    setenv("REQUEST_METHOD", (request->get_method()).c_str(), 1);
    setenv("SCRIPT_NAME", scriptname.c_str(), 1);); 
    setenv("SERVER_NAME", (request->gethost()).c_str(), 1);
    setenv("SERVER_PORT", (request->get_port()).c_str(), 1);
    setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
    setenv("SERVER_SOFTWARE", "webserver/1.1", 1);
    // setenv("HTTP_ACCEPT", (request->getaccept()).c_str(), 1);
    // setenv("HTTP_USER_AGENT", (request->getuseragent()).c_str(), 1);
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

void Cgi::executer(Request *request, Response *response, Location &location)
{
    // int fd[2];
    // int status;
    // pid_t pid;
    // std::stringstream ss;
    
    std::string path = location.get_root() + request->get_requestur();
    int request_fd = open(request->get_pathbody().c_str(), O_RDONLY);   
    int response_fd = open(response->_tmp_file_path.c_str(), O_RDONLY);
    const char *parm[3];
    parm[0] = _path.c_str();
    parm[0] = path.c_str(); 
    parm[1] = NULL;

    pid_t pid = fork();
    if (pid == -1)
    {
        //response->set_status(200);
        response->_status_code = 500;
        return;
    }
    if (pid == 0)
    {
        envMaker(request, location);
        close(STDERR_FILENO);
        if (hasBody)
        {
            dup2(request_fd, STDIN_FILENO);
            dup2(response_fd, STDOUT_FILENO);
            close(request_fd);
            close(response_fd);
        }
        else
        {
            dup2(response_fd, STDOUT_FILENO);
            close(request_fd);
            close(0);
        }
        int exitcode = execvp(_path.c_str(), (char *const *)parm);
        exit(exitcode);
        // if (exitcode == -1)
        // {
        //     //response->set_status(200);
        //     response->_status_code = 500;
        //     return;
        // }
    }
    else
    {   
        if (hasBody)
            close(request_fd);
        //close(response_fd);
        
        // waitpid(pid, NULL, 0);
    }
}


// else {

//             if (request->IsHasBody()) {

//                 close(request->GetBodyFd());
//             }

//             request->cgiPid = pid;
//             request->cgiRunning = true;

//         }
//     } else {

//         int state;
//         int status = waitpid(request->cgiPid, &state, WNOHANG);
//         if (status == -1) {
//             response->setStatusCode(INTERNAL_SERVER_ERROR);\
//             request->cgiRunning = false;
//             return;
//         } else if (status != 0) {
//             if (WIFEXITED(state) == 0) {
//                 response->setStatusCode(INTERNAL_SERVER_ERROR);

//                 request->cgiRunning = false;
//                 return;
//             }
//             response->getTempFile()._close();
//             response->getTempFile()._open();
//             response->readFromCgi();
//             request->cgiRunning = false;
//         }

//     }
// }