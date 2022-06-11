#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ErrorCodes.hpp"
#include "Request.hpp"
#include <dirent.h>

#define DIRCODE 2
#define FILECODE 1

class Response
{
	public:
		//std::string _response_file;
		std::string _headers;
		std::string _body_path;
		std::string _status_code;


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

};

std::map<int, std::string> code_map;

#endif