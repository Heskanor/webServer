#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>

#include "Request.hpp"
#include "location.hpp"

#define REDIRECTCODE 3
#define DIRCODE 2
#define FILECODE 1

// #define C200 "200 OK"
// #define C201 "201 Created"
// #define C202 "202 Accepted"
// #define C204 "204 No Content"
// #define C301 "301 Move Permanently"
// #define C400 "400 Bad Request"
// #define C403 "403 Forbidden"
// #define C404 "404 Not Found"
// #define C405 "405 Method Not Allowed"
// #define C413 "413 Payload Too Large"
// #define C414 "414 URI Too Long"
// #define C500 "500 Internal Server Error"
// #define C501 "501 Not Implemented"
// #define C502 "502 Bad Gateway"
// #define C505 "505 HTTP Version Not Supported"

class Response
{
	public:
		//std::string _response_file;
		std::string _headers;
		std::string _special_headers;
		std::string _body_path;
		std::string _status_code;
		std::string _content_type;
		std::string _content_length;
		std::string _tmp_file_path;

		std::map<std::string, std::string> http_code_map;

		Response(void) {}
		Response(const Response& src) {
			*this = src;
		}
		Response& operator=(const Response& rhs) {
			if (this != &rhs) {
				//_response_file = rhs._response_file;
				_headers = rhs._headers;
				_special_headers = rhs._special_headers;
				_body_path = rhs._body_path;
				_status_code = rhs._status_code;
				_content_type = rhs._content_type;
				_content_length = rhs._content_length;
				_tmp_file_path = rhs._tmp_file_path;
			}
			return *this;
		}
		~Response(void) {}

		class InvalidHttpVersion : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "505";
			}
		};
		class HttpMethodNotSupported : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "501";
			}
		};
		class HttpMethodNotAllowed : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "405";
			}
		};
		class NoMatchedLocation : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "404";
			}
		};
		class ForbiddenPath : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "403";
			}
		};
		class RedirectionDetected : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "301";
			}
		};
		class ConflictError : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "409";
			}
		};
		class InternalServerError : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "500";
			}
		};
};



Response server_response(Request& req, Server& server);

#endif