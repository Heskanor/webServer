#include "Response.hpp"

std::string deffault_error_page(std::string& code, std::string& msg)
{
	std::string page;
	page = "<html><head><title>" + code + " " + msg + "</title></head><body><center><h1>" 
	+ code + " " + msg + "</h1></center><hr><center>Webserver</center></body></html>";
	return page;
}

void init_code_map(void)
{
	code_map["200"] = "200 OK";
	code_map["201"] = "201 Created";
	code_map["301"] = "301 Move Permanently";
	code_map["400"] = "400 Bad Request";
	code_map["403"] = "403 Forbidden";
	code_map["404"] = "404 Not Found";
	code_map["405"] = "405 Method Not Allowed";
	code_map["413"] = "413 Payload Too Large";
	code_map["414"] = "414 URI Too Long";
	code_map["500"] = "500 Internal Server Error";
	code_map["501"] = "501 Not Implemented";
	code_map["502"] = "502 Bad Gateway";
	code_map["505"] = "505 HTTP Version Not Supported";
}

// HTTP/1.1 403 Forbidden
// Server: nginx/1.21.6
// Date: Sun, 12 Jun 2022 02:41:52 GMT
// Content-Type: text/html
// Content-Length: 555
// Connection: keep-alive

std::string set_date_header()
{
	time_t ttime = time(0);
    char* dt = ctime(&ttime);
	string date = string(dt);
	return (date.substr(0, date.size() - 1));
}

void set_response_headers(Request& req, Response& res)
{
	res._headers += "HTTP/1.1 " + code_map[res._status_code] + "\r\n";
	res._headers += "Server: Webserver/1.0\r\n";
	res._headers += "Date: " + set_date_header() + "\r\n";
	res._headers += "Content-Type: " + req.content_type + "\r\n";
	res._headers += "Content-Length: " + res._content_length + "\r\n";
	// res._headers += "Connection: keep-alive\r\n";
	if (res._special_headers != "")
		res._headers += res._special_headers + "\r\n";
	res._headers += "\r\n";
}

int check_if_entity_exists(std::string path)
{
	struct stat st;
	if (stat(path.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return DIRCODE;
		else if (S_ISREG(st.st_mode))
			return FILECODE;
	}
	return 0;
}

void check_http_version(std::string version)
{
	if (version != "HTTP/1.1")
	{
		throw Response::InvalidHttpVersion();
	}
}

void check_supported_methods(std::string method)
{
	if (method != "GET" && method != "POST" && method != "DELETE")
	{
		throw Response::HttpMethodNotSupported();
	}
}


Location find_matched_location(std::string& path, std::vector<Location>& locations)
{
	if (path != "")
	{
		int nbr_locations = locations.size();
		for (int i = 0; i < nbr_locations; i++)
		{
			if (locations[i].path == path)
				return locations[i];
		}
		size_t found = path.find_last_of("/");
		if (found != std::string::npos)
		{
			std::string path_without_last_slash = path.substr(0, found);
			return find_matched_location(path_without_last_slash, locations);
		}
	}
	throw Response::NoMatchedLocation();
}

void check_allowed_methods(Response& res, std::string method, std::vector<std::string>& allowed_methods)
{
	if (std::find(allowed_methods.begin(), allowed_methods.end(), method) == allowed_methods.end())
	{
		res._status_code = "405";
		res._special_headers = "Allow: " + string_join(allowed_methods, ", ");
		throw Response::HttpMethodNotAllowed();
	}
}

void redirect_response(std::pair<std::string, std::string>& redirection, std::string& redirection_code, std::string& redirection_path, Response& res)
{
	std::string new_status_code = redirection_code;
	std::string new_location = redirection_path;
	std::string location_header = "Location: " + new_location + "\r\n";
	res._status_code = new_status_code;
	set_response_headers(req, res, location_header);
}

void create_autoindex_file(std:string directory, std::vector<std::string>& entities, Response& res)
{
	std::string file_path = "/tmp/autoindex.html";
	std::ofstream file;
	file.open(file_path);
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Index of " << directory << "</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<h1>Index of "<< directory <<"</h1>\n";
	file << "<hr>\n";
	file << "<pre>\n";
	file << "<a href=" << "../" << ">../</a>\n";
	for (int i = 0; i < entities.size(); i++)
	{
		file << "<a href=\"" << entities[i] << "\">" << entities[i] << "</a>\n";
	}
	file << "</pre>\n";
	file << "<hr>\n";
	file << "</body>\n";
	file << "</html>\n";
	set_response_headers(req, res, "");
	res._body_path = file_path;
	res._status_code = "200";
	// set content type and length
	file.close();
}

bool check_for_autoindex(std::string directory, Response& res)
{
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> entities;

	if ((dir = opendir(directory)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			entities.push_back(ent->d_name);
		}
		closedir(dir);
	}
	else
		throw Response::ForbiddenPath();
	create_autoindex_file(directory, entities, res);
}

void check_for_index_file(Location& location, Response& res)
{
	if (!location._index.empty())
	{
		int nbr_indexes = location._index.size();
		for (int i = 0; i < nbr_indexes; i++)
		{
			int index_code = check_if_entity_exists(location._index[i]);
			if (!index_code)
				continue;
			if (index_code == FILECODE && access(location._index[i].c_str(), R_OK) == 0)
			{
				// check if location has cgi
				// set content type and length
				res._body_path = location._index[i];
				res._status_code = "200";
				return true;
			}
			else
				throw Response::ForbiddenPath();		
		}
	}
	return false;
}

void check_directory_resource(std::string& resource, Location& location, Response& res)
{
	bool index_file = check_for_index_file(location, res);
	if (!index_file && location.autoindex)
		check_for_autoindex(resource, res);
	else if (!index_file && !location.autoindex)
		throw Response::ForbiddenPath();
}

int requested_resource_by_delete(std::string& resource, Location& location, Response& res)
{
	struct stat st;
	if (stat(resource.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			if (resource.back() != '/')
				throw Response::ConflictError();
			if (access(resource.c_str(), W_OK))
				throw Response::InternalServerError();
			return DIRCODE;
		}
		else if (S_ISREG(st.st_mode))
		{
			if (access(resource.c_str(), W_OK))
				throw Response::ForbiddenPath();
			return FILECODE;
		}
	}
	throw Response::NoMatchedLocation();
}

int requested_resource_by_get(std::string& resource, Location& location, Response& res)
{
	struct stat st;
	if (stat(resource.c_str(), &st) == 0)
	{
		// will modify access permissions later depending on the method
		// if resource is directory with out / at the end redirect to directory/ before checking permission 
		if (S_ISDIR(st.st_mode))
		{
			if (resource.back() != '/')
			{
				resource += "/";
				redirect_response(location._redirections, "301", resource, res);
				return REDIRECTCODE;
			}
			if (access(resource.c_str(), R_OK))
				throw Response::ForbiddenPath();
			return (DIRCODE);
		}
		else if (S_ISREG(st.st_mode))
		{
			if (access(resource.c_str(), R_OK))
				throw Response::ForbiddenPath();
			return (FILECODE);
		}
	}
	else
		throw Response::NoMatchedLocation();
}

void response_to_delete(Response& res, Request& req, location& location)
{
	std::string resource = location._root + location._path;
	int resource_code = requested_resource_by_delete(resource, location, res);


}

void response_to_get(Response& res, Request& req, Location& location)
{
	std::string resource = location._root + location._path;
	int resource_code = requested_resource_by_get(resource, location, res);

	if (resource_code == REDIRECTCODE)
		return;
	if (resource_code == DIRCODE)
		check_directory_resource(resource, location, res);
	else if (resource_code == FILECODE)
	{
		// check if location has cgi
		// set content type and length
		res._status_code = "200";
		res._body_path = resource;
	}
}

Response server_response(Request& req, Server& server)
{
	Response res;
	init_code_map();
	vector<std::string> methods_arr = {"GET", "POST", "DELETE"}; 
	void (*methods_ptr[])(Response&, Request&, Location&) = {response_to_get, response_to_post, response_to_delete};

	try
	{
		check_http_version(req.get_httpversion(););
		check_supported_methods(req.get_method());
		Location location = find_matched_location(req.get_requestur(), server._locations);
		check_allowed_methods(req.get_method(), location._allowedMethods);
		if (location.redirection.first != "")
		{
			redirect_response(location._redirection, location._redirection.first,location._redirection.second, res);
			return res;
		}
		for (int i = 0; i < 3; i++)
			if (req.get_method() == methods_arr[i])
				return methods_ptr[i](res, req, location);
	}
	catch (std::exception& e)
	{
		char* error_code = e.what();
		// check for error pages
	}
}

