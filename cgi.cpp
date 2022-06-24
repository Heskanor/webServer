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
    std::string querrystring = "";
    if (path.find("?") != std::string::npos)
    {
        querrystring = path.substr(path.find("?") + 1);
        return querrystring;
    }
	return querrystring;
}

void Cgi::envMaker(Request *request, Location &location)
{
    std::string scriptname = location.get_root() + _path;
	// std::string scriptname = "/Users/hmahjour/Desktop/test.php";
    setenv("DOCUMENT_URI", ((request->get_requestur())).substr(0,request->get_requestur().find_first_of('?')).c_str(), 1);
    setenv("REQUEST_URI", request->get_requestur().c_str(), 1);
    setenv("AUTH_TYPE", "", 1);
    setenv("CONTENT_LENGTH", (request->getcontentlenght()).c_str(), 1);
    setenv("CONTENT_TYPE", (request->getcontent_type()).c_str(), 1); // need content type geter
    setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    setenv("PATH_INFO", ((request->get_requestur())).substr(0,request->get_requestur().find_first_of('?')).c_str(), 1); // subtr query string
    setenv("PATH_TRANSLATED", ((request->get_requestur())).substr(0,request->get_requestur().find_first_of('?')).c_str(), 1); // dir b7al path info
    setenv("QUERY_STRING", get_querrystring(request->get_requestur()).c_str(), 1);// after ?
    setenv("REMOTE_ADDR", "localhost", 1);
    setenv("REMOTE_HOST", "localhost", 1);// maybe like remote address
    setenv("REMOTE_IDENT", "", 1);
    setenv("REMOTE_USER", "", 1);
    setenv("REQUEST_METHOD", (request->get_method()).c_str(), 1);
    setenv("SCRIPT_NAME", scriptname.c_str(), 1); 
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
//int hasBody 
void cgi_reader(Response *resp, int fd)
{
    char buf[1024];
    int ret;
    std::string bd;
    int body_size;

    while ((ret = read(fd, buf, 1024)) > 0)
    {
        bd.append(buf, ret);
        if (bd.find("\r\n\r\n") != std::string::npos)
            break;
    }
    if(resp->_status_code != "500")
        resp->_status_code = "200";
    std::string headers = bd.substr(0, bd.find("\r\n\r\n") + 4);
    resp->_headers = headers;
    close (fd);
    struct stat st;
    if (stat(resp->_tmp_file_path.c_str(), &st) == 0)
        body_size = st.st_size;
    int cgiHeaderSize = headers.size();
    resp->_content_length = body_size - cgiHeaderSize;
}

void Cgi::executer(Request *request, Response *response, Location &location)
{
    int request_fd;
    int response_fd;

    std::string methode = request->get_method();
    std::string path = location.get_root() + remove_query_string(request->get_requestur());
    if (methode == "POST" || methode == "DELETE")
        request_fd = open(request->get_pathbody().c_str(), O_RDONLY);   
    response_fd = open(response->_tmp_file_path.c_str(), O_WRONLY);
    const char *parm[3];
    parm[0] = _path.c_str();
    std::cout << _path << " " << path << std::endl;
    parm[1] = path.c_str(); 
    parm[2] = NULL;
    pid_t cgi_pid;
	
    pid_t pid = fork();
    envMaker(request, location);
    if (pid == -1)
    {
        //response->set_status(200);
        response->_status_code = "500";
        return;
    }
    if (pid == 0)
    {
		write(2, methode.c_str(), 4);
        
        close(STDERR_FILENO);
        if (methode == "POST" || methode == "DELETE")
        {//write(2, methode.c_str(), 4);
            dup2(request_fd, STDIN_FILENO);
           dup2(response_fd, STDOUT_FILENO);
            close(request_fd);
            close(response_fd);
        }
        else
        {			//write(2, methode.c_str(), 4);
            dup2(response_fd, STDOUT_FILENO);
            close(STDIN_FILENO);
            close(response_fd);
        }
        int exitcode = execvp(_path.c_str(), (char *const *)parm);
        exit(exitcode);
    }
    else
    {   
        if (methode == "POST" || methode == "DELETE")
            close(request_fd);
        cgi_pid = pid;
    }
    int state;
    int status = waitpid(cgi_pid, &state, WNOHANG);
    if (status == -1) {
        response->_status_code = "500";
        return;
    }
    else if (status != 0)
    {
        if (WIFEXITED(state) == 0)
        {
            response->_status_code = "500";
            return;
        }
        cgi_reader(response,response_fd);
        //close response tmp file
    }
}